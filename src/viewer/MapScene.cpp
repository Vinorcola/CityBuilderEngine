#include "MapScene.hpp"

#include <QtWidgets/QGraphicsSceneMouseEvent>

#include "src/engine/element/dynamic/character/Character.hpp"
#include "src/engine/element/static/building/Building.hpp"
#include "src/engine/element/static/natureElement/NatureElement.hpp"
#include "src/engine/map/Map.hpp"
#include "src/engine/processing/TimeCycleProcessor.hpp"
#include "src/exceptions/OutOfRangeException.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/CharacterInformation.hpp"
#include "src/global/conf/Conf.hpp"
#include "src/global/conf/NatureElementInformation.hpp"
#include "src/viewer/construction/ConstructionCursor.hpp"
#include "src/viewer/element/graphics/DynamicElement.hpp"
#include "src/viewer/element/graphics/StaticElement.hpp"
#include "src/viewer/element/CharacterView.hpp"
#include "src/viewer/element/BuildingView.hpp"
#include "src/viewer/image/BuildingImage.hpp"
#include "src/viewer/image/CharacterImage.hpp"
#include "src/viewer/image/ImageLibrary.hpp"
#include "src/viewer/image/NatureElementImage.hpp"
#include "src/viewer/Tile.hpp"



MapScene::MapScene(const Conf& conf, const Map& map, const ImageLibrary& imageLibrary) :
    QGraphicsScene(),
    map(map),
    imageLibrary(imageLibrary),
    positioning(conf.getTileSize()),
    tiles(),
    buildings(),
    characters(),
    selectionElement(nullptr),
    animationClock(),
    currentTileLocation()
{
    setBackgroundBrush(QBrush(Qt::black));

    // Get the grass conf.
    auto& grassConf(conf.getNatureElementConf("grass"));
    auto& grassImage(imageLibrary.getNatureElementImage(grassConf));

    // Create the tiles and their graphics item.
    int line(0);
    int column(0);
    const QSize& mapSize(map.getSize());
    while (line < mapSize.height()) {
        // NOTE: Because we divide by 2 and casting as integer, we deliberately remove floating precision. However, the
        // adjustment needs to be 1 higher when "mapSize.width() - line" become negative. This is because -0.5 is cast
        // to 0 insted of 1.
        int adjust(line > mapSize.width() ? 1 : 2);
        while (column < (mapSize.width() - line + adjust) / 2) {
            auto tile(new Tile(
                positioning,
                MapCoordinates(column, line + column),
                *new StaticElement(positioning, MapSize(), grassImage.getImage())
            ));

            addItem(tile);
            tiles.append(tile);

            ++column;
        }
        ++line;
        column = -line / 2;
    }

    // Load existing elements.
    for (auto element : map.getBuildings()) {
        registerNewBuilding(element);
    }
    for (auto element : map.getNatureElements()) {
        registerNewNatureElement(*element);
    }

    connect(this, &MapScene::buildingCreationRequested, &map, &Map::createBuilding);
    connect(&map, &Map::buildingCreated, this, &MapScene::registerNewBuilding);
    connect(&map, &Map::characterCreated, this, &MapScene::registerNewCharacter);
    connect(map.getProcessor(), &TimeCycleProcessor::processFinished, this, &MapScene::refresh);

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



void MapScene::requestBuildingPositioning(const BuildingInformation& elementConf)
{
    if (selectionElement) {
        delete selectionElement;
    }
    selectionElement = new ConstructionCursor(
        positioning,
        map,
        map,
        elementConf,
        imageLibrary.getBuildingImage(elementConf)
    );
    addItem(selectionElement);
    connect(selectionElement, &ConstructionCursor::cancel, [this]() {
        delete selectionElement;
        selectionElement = nullptr;
    });
    connect(selectionElement, &ConstructionCursor::construct, [this](const BuildingInformation& buildingConf, QList<MapArea> area) {
        for (auto location : area) {
            emit buildingCreationRequested(buildingConf, location);
        }
    });
}



Tile& MapScene::getTileAt(const MapCoordinates& location) const
{
    for (auto tile : tiles) {
        if (tile->getCoordinates() == location) {
            return *tile;
        }
    }

    throw OutOfRangeException("Unable to find tile located at " + location.toString());
}



void MapScene::registerNewBuilding(QSharedPointer<const Building> element)
{
    buildings.append(
        new BuildingView(positioning, *this, imageLibrary, element)
    );
    if (selectionElement) {
        selectionElement->refresh();
    }
}



void MapScene::registerNewCharacter(QSharedPointer<const Character> element)
{
    characters.append(
        new CharacterView(positioning, *this, imageLibrary, element)
    );
}



void MapScene::registerNewNatureElement(const NatureElement& element)
{
    auto& tile(getTileAt(element.getArea().getLeft()));
    auto& natureElementImage(imageLibrary.getNatureElementImage(element.getConf()));

    tile.setStaticElement(new StaticElement(positioning, element.getArea().getSize(), natureElementImage.getImage()));
    // TODO: Handle higher size of nature elements by hiding covered tiles (see BuildingView).
}



void MapScene::refresh()
{
    // Refresh all the characters.
    auto iterator(characters.begin());
    while (iterator != characters.end()) {
        auto character(*iterator);
        character->updateFromEngineData();
        if (character->hasBeenDestroyed()) {
            iterator = characters.erase(iterator);
            delete character;
        } else {
            ++iterator;
        }
    }
}



void MapScene::timerEvent(QTimerEvent* /*event*/)
{
    for (auto building : buildings) {
        building->advanceAnimation();
    }
}



void MapScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    auto newMapCoordinates(positioning.getMapCoordinatesFromMouseCoordinates(event->scenePos()));
    if (newMapCoordinates != currentTileLocation) {
        currentTileLocation = newMapCoordinates;
        if (selectionElement) {
            selectionElement->displayAtLocation(newMapCoordinates);
        }
    }
}
