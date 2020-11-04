#include "Tile.hpp"

#include "src/viewer/element/graphics/DynamicElement.hpp"
#include "src/viewer/element/graphics/StaticElement.hpp"



Tile::Tile(const MapCoordinates& location, const QSizeF& baseTileSize, QGraphicsItem* groundElement) :
    QGraphicsObject(),
    location(location),
    groundElement(groundElement),
    staticElement(nullptr),
    dynamicElementList()
{
    setAcceptHoverEvents(true);
    setPos(
        (location.getY() + location.getX()) * (1.0 + baseTileSize.width() / 2.0),
        (location.getY() - location.getX()) * baseTileSize.height() / 2.0
    );
    groundElement->setParentItem(this);
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

    groundElement->setVisible(false);
}



void Tile::dropStaticElement()
{
    staticElement->setParentItem(nullptr);
    staticElement = nullptr;

    groundElement->setVisible(true);
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

    return groundElement->boundingRect();
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

    return groundElement->shape();
}



void Tile::hoverEnterEvent(QGraphicsSceneHoverEvent* /*event*/)
{
    emit isCurrentTile(this);
}
