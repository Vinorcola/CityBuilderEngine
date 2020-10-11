#include "DynamicElement.hpp"

#include "src/engine/element/dynamic/Character.hpp"
#include "src/viewer/SelectionElement.hpp"

const qreal BASE_DYNAMIC_ELEMENT_IMAGE_PADDING(5.0);



DynamicElement::DynamicElement(const QSizeF& baseTileSize, const QPixmap& elementImage, const MapCoordinates& location) :
    QGraphicsPixmapItem(elementImage),
    baseTileSize(baseTileSize)
{
    setAcceptedMouseButtons(Qt::RightButton);
    updateLocation(location);
}



void DynamicElement::updateLocation(const MapCoordinates& location)
{
    auto tileLocation(location.getRounded());

    qreal xBase(baseTileSize.width() / 2.0 - pixmap().width() / 2.0);
    qreal yBase(-pixmap().height() + baseTileSize.height() / 2.0 + BASE_DYNAMIC_ELEMENT_IMAGE_PADDING);

    qreal xDiff(location.getX() - tileLocation.getX());
    qreal yDiff(location.getY() - tileLocation.getY());

    qreal xNew(xBase + xDiff * baseTileSize.width() / 2.0 + yDiff * baseTileSize.width() / 2.0);
    qreal yNew(yBase - xDiff * baseTileSize.height() / 2.0 + yDiff * baseTileSize.height() / 2.0);

    setPos(xNew, yNew);
}
