#include "MapScene.hpp"

#include "src/engine/element/dynamic/Character.hpp"
#include "src/engine/element/static/Building.hpp"
#include "src/engine/element/static/NatureElement.hpp"
#include "src/engine/map/Map.hpp"
#include "src/engine/processing/TimeCycleProcessor.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/CharacterInformation.hpp"
#include "src/global/conf/Conf.hpp"
#include "src/global/conf/NatureElementInformation.hpp"
#include "src/viewer/element/graphics/StaticElement.hpp"
#include "src/viewer/image/BuildingImage.hpp"
#include "src/viewer/image/CharacterImage.hpp"
#include "src/viewer/image/ImageLibrary.hpp"
#include "src/viewer/image/NatureElementImage.hpp"
#include "src/viewer/DynamicElement.hpp"
#include "src/viewer/SelectionElement.hpp"
#include "src/viewer/Tile.hpp"

const QSizeF BASE_TILE_SIZE(58, 30);



MapScene::MapScene(const Conf& conf, const Map& map, const ImageLibrary& imageLibrary) :
    QGraphicsScene(),
    map(map),
    imageLibrary(imageLibrary),
    tileList(),
    dynamicElementList(),
    selectionElement(new SelectionElement(BASE_TILE_SIZE))
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
                MapCoordinates(column, line + column),
                BASE_TILE_SIZE,
                new StaticElement(BASE_TILE_SIZE, MapSize(1), grassImage.getImage())
            ));

            addItem(tile);
            tileList.append(tile);
            connect(tile, &Tile::isCurrentTile, this, &MapScene::currentTileChanged);

            ++column;
        }
        ++line;
        column = -line / 2;
    }

    // Attach the selection element.
    addItem(selectionElement);

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
}



void MapScene::requestBuildingPositioning(const BuildingInformation* elementConf)
{
    selectionElement->setBuildingType(elementConf);
}



void MapScene::requestBuildingCreation(const BuildingInformation* elementConf, const MapArea& area)
{
    emit buildingCreationRequested(*elementConf, area);
}



void MapScene::registerNewBuilding(QSharedPointer<const Building> element)
{
    Tile* tile(getTileAt(element->getArea().getLeft()));
    auto& buildingImage(imageLibrary.getBuildingImage(element->getConf()));

    tile->setStaticElement(new StaticElement(BASE_TILE_SIZE, element->getConf().getSize(), buildingImage.getInactiveImage()));
    maskCoveredTiles(tile, element->getConf().getSize());
}



void MapScene::registerNewCharacter(const Character& element)
{
    auto& characterImage(imageLibrary.getCharacterImage(element.getConf()));
    DynamicElement* graphicsItem(new DynamicElement(BASE_TILE_SIZE, &element, characterImage.getImage()));
    dynamicElementList.append(graphicsItem);

    Tile* tile(getTileAt(element.getCurrentLocation().getRounded()));
    tile->registerDynamicElement(graphicsItem);
}



void MapScene::registerNewNatureElement(const NatureElement& element)
{
    Tile* tile(getTileAt(element.getArea().getLeft()));
    auto& natureElementImage(imageLibrary.getNatureElementImage(element.getConf()));

    tile->setStaticElement(new StaticElement(BASE_TILE_SIZE, element.getArea().getSize(), natureElementImage.getImage()));
    maskCoveredTiles(tile, element.getArea().getSize());
}



void MapScene::refresh()
{
    // Refresh all the dynamic elements.
    auto iterator(dynamicElementList.begin());
    while (iterator != dynamicElementList.end()) {
        auto element(*iterator);
        if (element->stillExists()) {
            const MapCoordinates& previousTileLocation(static_cast<Tile*>(element->parentItem())->getCoordinates());
            MapCoordinates newTileLocation(element->getCoordinates().getRounded());
            if (newTileLocation != previousTileLocation) {
                // Dynamic element just switch to another tile.
                getTileAt(previousTileLocation)->unregisterDynamicElement(element);
                getTileAt(newTileLocation)->registerDynamicElement(element);
            }

            element->refresh();
            ++iterator;
        } else {
            removeItem(element);
            delete element;
            iterator = dynamicElementList.erase(iterator);
        }
    }

    // Refresh the selection element.
    if (selectionElement->isVisible()) {
        refreshSelectionElement();
    }
}



Tile* MapScene::getTileAt(const MapCoordinates& location)
{
    for (auto tile : tileList) {
        if (tile->getCoordinates() == location) {
            return tile;
        }
    }

    return nullptr;
}



void MapScene::maskCoveredTiles(Tile* tile, const MapSize& elementSize)
{
    if (elementSize.getValue() > 1) {
        MapArea area(tile->getCoordinates(), elementSize);
        auto left(area.getLeft());
        auto right(area.getRight());
        auto current(left.getEast());

        while (current.getY() <= right.getY()) {
            while (current.getX() <= right.getX()) {
                getTileAt(current)->setVisible(false);
                current = current.getEast();
            }
            current.setX(left.getX());
            current = current.getSouth();
        }
    }
}



void MapScene::refreshSelectionElement()
{
    if (map.isFreeArea(selectionElement->getCoveredArea())) {
        selectionElement->setGood();
    } else {
        selectionElement->setBad();
    }
}



void MapScene::currentTileChanged(Tile* currentTile)
{
    if (selectionElement->isVisible()) {
        selectionElement->attachToTile(*currentTile);
        refreshSelectionElement();
    }
}
