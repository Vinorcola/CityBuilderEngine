#include "StaticElement.hpp"

#include "src/engine/map/MapSize.hpp"
#include "src/viewer/image/Image.hpp"


StaticElement::StaticElement(const QSizeF& baseTileSize, const MapSize& elementSize, const Image& elementImage) :
    QGraphicsPixmapItem(elementImage.getPixmap()),
    shapePath(),
    animationItem(nullptr)
{
    setAcceptedMouseButtons(Qt::RightButton);

    qreal elementSizeValue(elementSize.getValue());
    qreal halfBaseTileSizeHeight(baseTileSize.height()/ 2.0);
    qreal halfBaseTileSizeWidth(baseTileSize.width() / 2.0);

    // Move the image at the right place.
    // NOTE: A static element is attached to the tile located at the left corner of it's area. The height will depends
    // on the element size, since we must align it with the bottom tile of it's area.
    setPos(0, (elementSizeValue + 1) * halfBaseTileSizeHeight - elementImage.getPixmap().height());

    // Create shape path.
    // NOTE: The shape path must represent the element base on the map (the zone that covers the tiles). It must not
    // take the element extra height into account.
    shapePath.moveTo(0                                       , halfBaseTileSizeHeight                            ); // Left corner
    shapePath.lineTo(elementSizeValue * halfBaseTileSizeWidth, -(elementSizeValue - 1.0) * halfBaseTileSizeHeight); // Top corner
    shapePath.lineTo(elementSizeValue * baseTileSize.width() , halfBaseTileSizeHeight                            ); // Right corner
    shapePath.lineTo(elementSizeValue * halfBaseTileSizeWidth, (elementSizeValue + 1.0) * halfBaseTileSizeHeight ); // Bottom corner
    shapePath.closeSubpath();
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
