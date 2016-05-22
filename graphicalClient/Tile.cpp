#include "Tile.hpp"





Tile::Tile(const MapCoordinates& location, const QSizeF& baseTileSize, QObject* parent) :
    QObject(parent),
    location(location),
    graphicalAttachPoint(
        (location.getY() + location.getX()) * baseTileSize.width() / 2.0,
        (location.getY() - location.getX()) * baseTileSize.height() / 2.0
    ),
    graphicsItemlist()
{

}





void Tile::pushGraphicsItem(StaticElementGraphicsItem* graphicsItem)
{
    graphicsItem->setPos(graphicalAttachPoint);
    graphicsItemlist.push(graphicsItem);
}





StaticElementGraphicsItem* Tile::popGraphicsItem()
{
    return graphicsItemlist.pop();
}
