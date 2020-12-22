#include "StaticElement.hpp"

#include "src/viewer/image/Image.hpp"
#include "src/viewer/Positioning.hpp"



StaticElement::StaticElement(
    const Positioning& positioning,
    const TileAreaSize& elementSize,
    const Image& elementImage
) :
    QGraphicsPixmapItem(elementImage.getPixmap()),
    shapePath(positioning.getTileAreaPainterPath(elementSize)),
    animationItem(nullptr)
{
    setPos(positioning.getStaticElementPositionInTile(elementSize, elementImage.getPixmap().height()));
}



void StaticElement::setAnimationImage(const Image& image)
{
    if (!animationItem) {
        animationItem = new QGraphicsPixmapItem(this);
        animationItem->setParentItem(this);
    }
    animationItem->setVisible(true);
    animationItem->setPixmap(image.getPixmap());
    animationItem->setPos(image.getPosition());
}



void StaticElement::dropAnimationImage()
{
    if (animationItem) {
        animationItem->setVisible(false);
    }
}



QPainterPath StaticElement::shape() const
{
    return shapePath;
}
