#include "Tile.hpp"





Tile::Tile(const MapCoordinates& location, const QSizeF& baseTileSize) :
    QGraphicsItem(),
    location(location),
    graphicsItemList()
{
    setPos(
        (location.getY() + location.getX()) * baseTileSize.width() / 2.0,
        (location.getY() - location.getX()) * baseTileSize.height() / 2.0
    );
}





const MapCoordinates& Tile::getCoordinates() const
{
    return location;
}





void Tile::pushGraphicsItem(StaticElementGraphicsItem* graphicsItem)
{
    if (graphicsItemList.size() > 0)
    {
        // Hide previous graphics item.
        graphicsItemList.last()->setVisible(false);
    }

    graphicsItem->setParentItem(this);
    graphicsItem->setVisible(true);
    graphicsItemList.push(graphicsItem);
}





StaticElementGraphicsItem* Tile::popGraphicsItem()
{
    auto last(graphicsItemList.pop());
    last->setParentItem(nullptr);

    if (graphicsItemList.size() > 0)
    {
        // Show last item.
        graphicsItemList.last()->setVisible(true);
    }

    return last;
}





QRectF Tile::boundingRect() const
{
    if (graphicsItemList.size() > 0)
    {
        return graphicsItemList.last()->boundingRect();
    }

    return QRectF();
}





void Tile::paint(QPainter* /*painter*/, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    // Nothing to paint here. It is the last child element of the stack that will be painted.
}
