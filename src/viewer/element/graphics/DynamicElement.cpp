#include "DynamicElement.hpp"

#include "src/viewer/image/Image.hpp"
#include "src/viewer/Positioning.hpp"



DynamicElement::DynamicElement(
    const Positioning& positioning,
    const Image& elementImage,
    const DynamicElementCoordinates& location
) :
    QGraphicsItem(),
    imageItem(elementImage.getPixmap(), this)
{
    setPos(positioning.getDynamicElementPositionInTile(location));
    imageItem.setPos(elementImage.getPosition());
}



void DynamicElement::setImage(const Image& image)
{
    imageItem.setPixmap(image.getPixmap());
    imageItem.setPos(image.getPosition());
}



void DynamicElement::updateLocation(const QPointF& positionOnTile)
{
    setPos(positionOnTile);
}



QRectF DynamicElement::boundingRect() const
{
    return {};
}



void DynamicElement::paint(QPainter* /*painter*/, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    // Nothing to draw here.
}
