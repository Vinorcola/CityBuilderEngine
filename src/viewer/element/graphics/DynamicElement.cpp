#include "DynamicElement.hpp"

#include "src/viewer/image/Image.hpp"



DynamicElement::DynamicElement(const QSizeF& baseTileSize, const Image& elementImage, const QPointF& positionOnTile) :
    QGraphicsItem(),
    baseTileSize(baseTileSize),
    imageItem(elementImage.getPixmap(), this)
{
    setPos(positionOnTile);
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
