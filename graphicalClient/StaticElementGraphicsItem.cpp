#include "StaticElementGraphicsItem.hpp"





StaticElementGraphicsItem::StaticElementGraphicsItem(const QSizeF& baseTileSize, const MapSize& elementSize, const QPixmap& elementImage) :
    QGraphicsItem(),
    shapePath(),
    imageGraphicsItem(new QGraphicsPixmapItem(elementImage, this))
{
    qreal elementSizeValue(elementSize.getValue());
    qreal baseTileSizeHeight(baseTileSize.height());
    qreal baseTileSizeWidth(baseTileSize.width());
    qreal halfBaseTileSizeHeight(baseTileSizeHeight / 2.0);
    qreal halfBaseTileSizeWidth(baseTileSizeWidth / 2.0);

    // Move the graphics item horizontally according to the element size.
    // NOTE: The position needs to be set according to the left tile coordinates.
    setPos(
        0,
        -(elementSizeValue - 1) * halfBaseTileSizeHeight
    );

    // Move the image at the right place.
    qreal zoneHeight(elementSizeValue * baseTileSizeHeight);
    qreal zoneWidth(elementSizeValue * baseTileSizeWidth);
    qreal extraImageHeight(qMax(0.0, elementImage.height() - zoneHeight));
    qreal extraImageWidth(qMax(0.0, elementImage.width() - zoneWidth));
    imageGraphicsItem->setPos(-extraImageWidth / 2.0, -extraImageHeight);

    // Create shape path.
    // NOTE: The shape path must turn arround the element size on the map.
    shapePath.moveTo( elementSizeValue * halfBaseTileSizeWidth, 0                                         );
    shapePath.lineTo( elementSizeValue * baseTileSizeWidth    , elementSizeValue * halfBaseTileSizeHeight );
    shapePath.lineTo( elementSizeValue * halfBaseTileSizeWidth, elementSizeValue * baseTileSizeHeight     );
    shapePath.lineTo( 0                                       , elementSizeValue * halfBaseTileSizeHeight );
    shapePath.closeSubpath();
}





QRectF StaticElementGraphicsItem::boundingRect() const
{
    return imageGraphicsItem->boundingRect();
}





void StaticElementGraphicsItem::paint(QPainter* /*painter*/, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    // Nothing to paint here. It is the children elements that will be painted (the imageGraphicsItem particularly).
}





QPainterPath StaticElementGraphicsItem::shape() const
{
    return shapePath;
}
