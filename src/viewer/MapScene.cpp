#include "MapScene.hpp"

#include <QtWidgets/QGraphicsSceneMouseEvent>

#include "src/exceptions/OutOfRangeException.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/CharacterInformation.hpp"
#include "src/global/conf/Conf.hpp"
#include "src/global/conf/NatureElementInformation.hpp"
#include "src/global/geometry/TileAreaSize.hpp"
#include "src/global/state/MapState.hpp"
#include "src/global/state/NatureElementState.hpp"
#include "src/global/state/State.hpp"
#include "src/ui/BuildingDetailsDialog.hpp"
#include "src/ui/DialogDisplayer.hpp"
#include "src/viewer/construction/ConstructionCursor.hpp"
#include "src/viewer/element/graphics/DynamicElement.hpp"
#include "src/viewer/element/graphics/StaticElement.hpp"
#include "src/viewer/element/BuildingView.hpp"
#include "src/viewer/element/CharacterView.hpp"
#include "src/viewer/image/BuildingImage.hpp"
#include "src/viewer/image/CharacterImage.hpp"
#include "src/viewer/image/ImageLibrary.hpp"
#include "src/viewer/image/NatureElementImage.hpp"
#include "src/viewer/TileView.hpp"



MapScene::MapScene(
    const Conf& conf,
    const AreaCheckerInterface& areaChecker,
    const RoadPathGeneratorInterface& roadPathGenerator,
    DialogDisplayer& dialogDisplayer,
    const MapState& mapState,
    const State& initialState
) :
    QGraphicsScene(),
    areaChecker(areaChecker),
    roadPathGenerator(roadPathGenerator),
    imageLibrary(conf),
    positioning(conf.getTileSize()),
    dialogDisplayer(dialogDisplayer),
    tiles(),
    buildings(),
    characters(),
    buildingLocationCache(),
    selectionElement(nullptr),
    animationClock(),
    currentTileLocation(0, 0)
{
    setBackgroundBrush(QBrush(Qt::black));

    // Get the grass conf.
    auto& grassConf(conf.getNatureElementConf("grass"));
    auto& grassImage(imageLibrary.getNatureElementImage(grassConf));

    // Create the tiles and their graphics item.
    for (int x = 0; x < mapState.size.height(); x++)
    {
        for (int y = 0; y < mapState.size.width(); y++)
        {
            TileCoordinates coordinates(x,y);

            auto tile(new TileView(
                positioning,
                coordinates,
                *new StaticElement(positioning, TileAreaSize(1), grassImage.getImage())
            ));

            addItem(tile);
            tiles.insert(coordinates.hash(), tile);
        }
    }


    // Load existing elements.
    for (auto buildingState : initialState.buildings) {
        registerNewBuilding(buildingState);
    }
    for (auto natureElementState : initialState.natureElements) {
        registerNewNatureElement(natureElementState);
    }

    animationClock.start(100, this);
}



MapScene::~MapScene()
{
    qDeleteAll(buildings);
    qDeleteAll(characters);
    if (selectionElement) {
        delete selectionElement;
    }
    qDeleteAll(tiles);
}



TileView& MapScene::getTileAt(const TileCoordinates& location) const
{
    if (!tiles.contains(location.hash())) {
        throw OutOfRangeException("Unable to find tile located at " + location.hash());
    }

    return *tiles.value(location.hash());
}



void MapScene::requestBuildingPositioning(const BuildingInformation& elementConf)
{
    if (selectionElement) {
        delete selectionElement;
    }
    selectionElement = new ConstructionCursor(
        positioning,
        areaChecker,
        roadPathGenerator,
        elementConf,
        imageLibrary.getBuildingImage(elementConf)
    );
    addItem(selectionElement);
    connect(selectionElement, &ConstructionCursor::cancel, [this]() {
        delete selectionElement;
        selectionElement = nullptr;
    });
    connect(
        selectionElement,
        &ConstructionCursor::construct,
        [this](const BuildingInformation& buildingConf, QList<TileCoordinates> locations, Direction direction) {
            for (auto location : locations) {
                emit buildingCreationRequested(buildingConf, location, direction);
            }
        }
    );
}



void MapScene::requestBuildingRotation()
{
    if (selectionElement) {
        selectionElement->rotateBuilding();
    }
}



void MapScene::registerNewBuilding(const BuildingState& buildingState)
{
    auto buildingView(new BuildingView(positioning, *this, imageLibrary, buildingState));
    buildings.insert(buildingState.id, buildingView);
    for (auto coordinates : buildingState.area) {
        buildingLocationCache.insert(coordinates.hash(), buildingView);
    }
    if (selectionElement) {
        selectionElement->refresh();
    }
}



void MapScene::registerNewCharacter(const CharacterState& characterState)
{
    characters.insert(
        characterState.id,
        new CharacterView(positioning, *this, imageLibrary, characterState)
    );
}



void MapScene::registerNewNatureElement(const NatureElementState& natureElementState)
{
    auto& tile(getTileAt(natureElementState.area.leftCorner()));
    auto& natureElementImage(imageLibrary.getNatureElementImage(natureElementState.type));

    tile.setStaticElement(new StaticElement(
        positioning,
        natureElementState.area.size(),
        natureElementImage.getImage()
    ));
    // TODO: Deletion of nature elements is not handled. We should handle it the same way as buildings since the player
    // may be able to see an information dialog.
    // TODO: Handle higher size of nature elements by hiding covered tiles (see BuildingView).
}



void MapScene::refresh(const State& state)
{
    auto buildingsToDestroy(buildings.keys());
    for (auto& buildingState : state.buildings) {
        if (buildings.contains(buildingState.id)) {
            // Update existing building.
            buildings.value(buildingState.id)->update(buildingState);
            buildingsToDestroy.removeOne(buildingState.id);
        }
        else {
            // Create new building.
            registerNewBuilding(buildingState);
        }
    }
    for (auto buildingId : buildingsToDestroy) {
        // Delete not found buildings.
        buildings.value(buildingId)->destroy();
        delete buildings.take(buildingId);
    }

    auto charactersToDestroy(characters.keys());
    for (auto& characterState : state.characters) {
        if (characters.contains(characterState.id)) {
            // Update existing character.
            characters.value(characterState.id)->update(characterState);
            charactersToDestroy.removeOne(characterState.id);
        }
        else {
            // Create new character.
            registerNewCharacter(characterState);
        }
    }
    for (auto characterId : charactersToDestroy) {
        // Delete not found characters.
        characters.value(characterId)->destroy();
        delete characters.take(characterId);
    }
}



void MapScene::timerEvent(QTimerEvent* /*event*/)
{
    for (auto building : buildings) {
        building->advanceAnimation();
    }
}



void MapScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (!selectionElement && event->button() == Qt::RightButton) {
        auto buildingView(buildingLocationCache.value(currentTileLocation.hash()));
        if (buildingView && buildingView->getCurrentState().type.getType() != BuildingInformation::Type::Road) {
            displayBuildingDetailsDialog(buildingView->getCurrentState());
            return;
        }
    }

    QGraphicsScene::mouseReleaseEvent(event);
}



void MapScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    auto newMapCoordinates(positioning.getTileCoordinatesFromMouseCoordinates(event->scenePos()));
    if (newMapCoordinates != currentTileLocation) {
        currentTileLocation = newMapCoordinates;
        if (selectionElement) {
            selectionElement->displayAtLocation(newMapCoordinates);
        }
    }
}



void MapScene::displayBuildingDetailsDialog(const BuildingState& buildingState)
{
    BuildingDetailsDialog dialog(buildingState);
    dialogDisplayer.displayDialog(dialog);
}
