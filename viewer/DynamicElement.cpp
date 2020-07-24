#include "DynamicElement.hpp"

#include "engine/element/dynamic/Character.hpp"
#include "viewer/SelectionElement.hpp"

const qreal BASE_DYNAMIC_ELEMENT_IMAGE_PADDING(5.0);



DynamicElement::DynamicElement(const QSizeF& baseTileSize, const Character* element, const QPixmap& elementImage) :
    QGraphicsPixmapItem(elementImage),
    baseTileSize(baseTileSize),
    element(element)
{
    setAcceptedMouseButtons(Qt::RightButton);

    refresh();
    setZValue(1.0);
}



bool DynamicElement::stillExists()
{
    return element;
}



MapCoordinates DynamicElement::getCoordinates() const
{
    if (element) {
        return element->getCurrentLocation();
    }

    return MapCoordinates();
}



void DynamicElement::refresh()
{
    if (element) {
        const MapCoordinates& location(element->getCurrentLocation());
        MapCoordinates roundedLocation(location.getRounded());

        qreal xBase(baseTileSize.width() / 2.0 - pixmap().width() / 2.0);
        qreal yBase(-pixmap().height() + baseTileSize.height() / 2.0 + BASE_DYNAMIC_ELEMENT_IMAGE_PADDING);

        qreal xDiff(location.getX() - roundedLocation.getX());
        qreal yDiff(location.getY() - roundedLocation.getY());

        qreal xNew(xBase + xDiff * baseTileSize.width() / 2.0 + yDiff * baseTileSize.width() / 2.0);
        qreal yNew(yBase - xDiff * baseTileSize.height() / 2.0 + yDiff * baseTileSize.height() / 2.0);

        setPos(xNew, yNew);
    }
}
