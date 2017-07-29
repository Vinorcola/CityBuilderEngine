#include "Tile.hpp"



Tile::Tile(const MapCoordinates& location, const QSizeF& baseTileSize) :
    QGraphicsObject(),
    location(location),
    staticElementList(),
    dynamicElementList()
{
    setAcceptHoverEvents(true);
    setPos(
        (location.getY() + location.getX()) * baseTileSize.width() / 2.0,
        (location.getY() - location.getX()) * baseTileSize.height() / 2.0
    );
}



const MapCoordinates& Tile::getCoordinates() const
{
    return location;
}



void Tile::pushStaticElement(StaticElement* element)
{
    if (staticElementList.size() > 0) {
        // Hide previous graphics item.
        staticElementList.last()->setVisible(false);
    }

    element->setParentItem(this);
    element->setVisible(true);
    staticElementList.push(element);
}



StaticElement* Tile::popStaticElement()
{
    auto element(staticElementList.pop());
    element->setParentItem(nullptr);

    if (staticElementList.size() > 0) {
        // Show last item.
        staticElementList.last()->setVisible(true);
    }

    return element;
}



void Tile::registerDynamicElement(DynamicElement* element)
{
    element->setParentItem(this);
    element->setVisible(true);
    dynamicElementList.append(element);
}



void Tile::unregisterDynamicElement(DynamicElement* element)
{
    dynamicElementList.removeOne(element);
}



QRectF Tile::boundingRect() const
{
    if (staticElementList.size() > 0) {
        return staticElementList.last()->boundingRect();
    }

    return QRectF();
}



void Tile::paint(QPainter* /*painter*/, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    // Nothing to paint here. It is the last child element of the stack that will be painted.
}



QPainterPath Tile::shape() const
{
    if (staticElementList.size() > 0) {
        return staticElementList.last()->shape();
    }

    return QGraphicsObject::shape();
}



void Tile::hoverEnterEvent(QGraphicsSceneHoverEvent* /*event*/)
{
    emit isCurrentTile(this);
}
