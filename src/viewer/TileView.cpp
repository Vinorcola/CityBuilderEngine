#include "TileView.hpp"

#include "src/viewer/Positioning.hpp"



TileView::TileView(const Positioning& positioning, const MapCoordinates& location, QGraphicsItem& groundElement) :
    QGraphicsItem(),
    location(location),
    groundElement(groundElement),
    staticElement(nullptr)
{
    setAcceptHoverEvents(true);
    setPos(positioning.getTilePosition(location));
    groundElement.setParentItem(this);
}



const MapCoordinates& TileView::getCoordinates() const
{
    return location;
}



void TileView::setStaticElement(QGraphicsItem* staticElement)
{
    if (this->staticElement) {
        staticElement->setParentItem(nullptr);
    }

    this->staticElement = staticElement;
    staticElement->setParentItem(this);

    groundElement.setVisible(false);
}



void TileView::dropStaticElement()
{
    staticElement->setParentItem(nullptr);
    staticElement = nullptr;

    groundElement.setVisible(true);
}



void TileView::registerDynamicElement(QGraphicsItem* element)
{
    element->setParentItem(this);
    element->setVisible(true);
}



void TileView::moveDynamicElementTo(QGraphicsItem* element, TileView& other)
{
    element->setParentItem(&other);
}



void TileView::unregisterDynamicElement(QGraphicsItem* element)
{
    element->setParentItem(nullptr);
}



QRectF TileView::boundingRect() const
{
    if (staticElement) {
        return staticElement->boundingRect();
    }

    return groundElement.boundingRect();
}



void TileView::paint(QPainter* /*painter*/, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    // Nothing to paint here. It is the last child element of the stack that will be painted.
}



QPainterPath TileView::shape() const
{
    if (staticElement) {
        return staticElement->shape();
    }

    return groundElement.shape();
}
