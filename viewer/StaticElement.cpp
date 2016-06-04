#include "StaticElement.hpp"





StaticElement::StaticElement(const QSizeF& baseTileSize, const MapSize& elementSize, const QPixmap& elementImage) :
    QGraphicsPixmapItem(elementImage),
    shapePath()
{
    qreal elementSizeValue(elementSize.getValue());
    qreal baseTileSizeHeight(baseTileSize.height());
    qreal baseTileSizeWidth(baseTileSize.width());
    qreal halfBaseTileSizeHeight(baseTileSizeHeight / 2.0);
    qreal halfBaseTileSizeWidth(baseTileSizeWidth / 2.0);

    // Move the image at the right place.
    qreal zoneHeight(elementSizeValue * baseTileSizeHeight);
    qreal zoneWidth(elementSizeValue * baseTileSizeWidth);
    qreal extraImageHeight(qMax(0.0, elementImage.height() - zoneHeight));
    qreal extraImageWidth(qMax(0.0, elementImage.width() - zoneWidth));
    setPos(-extraImageWidth / 2.0, -(elementSizeValue - 1) * halfBaseTileSizeHeight - extraImageHeight);

    // Create shape path.
    // NOTE: The shape path must represent the element base on the map. It must not take the element extra height.
    shapePath.moveTo( elementSizeValue * halfBaseTileSizeWidth, 0                                         );
    shapePath.lineTo( elementSizeValue * baseTileSizeWidth    , elementSizeValue * halfBaseTileSizeHeight );
    shapePath.lineTo( elementSizeValue * halfBaseTileSizeWidth, elementSizeValue * baseTileSizeHeight     );
    shapePath.lineTo( 0                                       , elementSizeValue * halfBaseTileSizeHeight );
    shapePath.closeSubpath();
}





QPainterPath StaticElement::shape() const
{
    return shapePath;
}
