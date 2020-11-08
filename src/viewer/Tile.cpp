#include "Tile.hpp"

#include "src/viewer/Positioning.hpp"



Tile::Tile(const Positioning& positioning, const MapCoordinates& location, QGraphicsItem& groundElement) :
    QGraphicsObject(),
    location(location),
    groundElement(groundElement),
    staticElement(nullptr)
{
    setAcceptHoverEvents(true);
    setPos(positioning.getTilePosition(location));
    groundElement.setParentItem(this);
}



const MapCoordinates& Tile::getCoordinates() const
{
    return location;
}



void Tile::setStaticElement(QGraphicsItem* staticElement)
{
    if (this->staticElement) {
        staticElement->setParentItem(nullptr);
    }

    this->staticElement = staticElement;
    staticElement->setParentItem(this);

    groundElement.setVisible(false);
}



void Tile::dropStaticElement()
{
    staticElement->setParentItem(nullptr);
    staticElement = nullptr;

    groundElement.setVisible(true);
}



void Tile::registerDynamicElement(QGraphicsItem* element)
{
    element->setParentItem(this);
    element->setVisible(true);
}



void Tile::moveDynamicElementTo(QGraphicsItem* element, Tile& other)
{
    element->setParentItem(&other);
}



void Tile::unregisterDynamicElement(QGraphicsItem* element)
{
    element->setParentItem(nullptr);
}



QRectF Tile::boundingRect() const
{
    if (staticElement) {
        return staticElement->boundingRect();
    }

    return groundElement.boundingRect();
}



void Tile::paint(QPainter* /*painter*/, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    // Nothing to paint here. It is the last child element of the stack that will be painted.
}



QPainterPath Tile::shape() const
{
    if (staticElement) {
        return staticElement->shape();
    }

    return groundElement.shape();
}



void Tile::hoverEnterEvent(QGraphicsSceneHoverEvent* /*event*/)
{
    emit isCurrentTile(this);
}
