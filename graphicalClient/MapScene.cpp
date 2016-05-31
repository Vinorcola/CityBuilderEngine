#include "MapScene.hpp"

#include <QDebug>

#include "engine/element/building/MaintenanceBuilding.hpp"
#include "engine/element/building/Road.hpp"



const QSizeF BASE_TILE_SIZE(58, 30);





MapScene::MapScene(const Map& map) :
    QGraphicsScene(),
    tileList(),
    dynamicElementList()
{
    setBackgroundBrush(QBrush(Qt::black));

    // Load the grass image.
    QPixmap grassImage("assets/img/grass.png");

    // Create the tiles and their graphics item.
    int line(0);
    int column(0);
    const QSize& mapSize(map.getSize());
    while (line < mapSize.height())
    {
        // NOTE: Because we divide by 2 and casting as integer, we deliberately remove floating precision. However, the
        // adjustment needs to be 1 higher when "mapSize.width() - line" become negative. This is because -0.5 is cast
        // to 0 insted of 1.
        int adjust(line > mapSize.width() ? 1 : 2);
        while (column < (mapSize.width() - line + adjust) / 2)
        {
            Tile* tile(new Tile(MapCoordinates(column, line + column), BASE_TILE_SIZE));
            tile->pushStaticElement(new StaticElement(BASE_TILE_SIZE, MapSize(1), grassImage));

            addItem(tile);
            tileList.append(tile);

            ++column;
        }
        ++line;
        column = -line / 2;
    }

    connect(&map, &Map::staticElementCreated, this, &MapScene::registerNewStaticElement);
    connect(&map, &Map::dynamicElementCreated, this, &MapScene::registerNewDynamicElement);
    connect(&map.getProcessor(), &TimeCycleProcessor::processFinished, this, &MapScene::refresh);
}





void MapScene::registerNewStaticElement(const QWeakPointer<AbstractStaticMapElement>& element)
{
    auto elementAccess(element.toStrongRef());
    if (elementAccess)
    {
        auto staticElement(elementAccess.data());
        Tile* tile(getTileAt(staticElement->getArea().getLeft()));

        if (dynamic_cast<Road*>(staticElement))
        {
            addStaticElementBuilding(tile, MapSize(1), QPixmap("assets/img/road"));
        }
        else if (dynamic_cast<MaintenanceBuilding*>(staticElement))
        {
            addStaticElementBuilding(tile, MapSize(2), QPixmap("assets/img/building.png"));
        }
    }
}





void MapScene::registerNewDynamicElement(const QWeakPointer<AbstractDynamicMapElement>& element)
{
    auto elementAccess(element.toStrongRef());
    if (elementAccess)
    {
        // Load the test images.
        QPixmap characterImage("assets/img/character.png");

        DynamicElement* graphicsItem(new DynamicElement(BASE_TILE_SIZE, element, characterImage));
        dynamicElementList.append(graphicsItem);

        Tile* tile(getTileAt(elementAccess->getCurrentLocation().getRounded()));
        tile->registerDynamicElement(graphicsItem);
    }
}





void MapScene::refresh()
{
    for (auto element : dynamicElementList)
    {
        const MapCoordinates& previousTileLocation(static_cast<Tile*>(element->parentItem())->getCoordinates());
        MapCoordinates newTileLocation(element->getCoordinates().getRounded());
        if (newTileLocation != previousTileLocation)
        {
            getTileAt(previousTileLocation)->unregisterDynamicElement(element);
            getTileAt(newTileLocation)->registerDynamicElement(element);
        }

        element->refresh();
    }
}





Tile* MapScene::getTileAt(const MapCoordinates& location)
{
    for (auto tile : tileList)
    {
        if (tile->getCoordinates() == location)
        {
            return tile;
        }
    }

    return nullptr;
}





void MapScene::addStaticElementBuilding(Tile* tile, const MapSize& elementSize, const QPixmap& elementImage)
{
    tile->pushStaticElement(new StaticElement(BASE_TILE_SIZE, elementSize, elementImage));

    if (elementSize.getValue() > 1)
    {
        MapArea area(tile->getCoordinates(), elementSize);
        auto left(area.getLeft());
        auto right(area.getRight());
        auto current(left.getEast());

        while (current.getY() <= right.getY())
        {
            while (current.getX() <= right.getX())
            {
                getTileAt(current)->setVisible(false);
                current = current.getEast();
            }
            current.setX(left.getX());
            current = current.getSouth();
        }
    }
}
