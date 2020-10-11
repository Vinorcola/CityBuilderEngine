#ifndef DYNAMICELEMENT_HPP
#define DYNAMICELEMENT_HPP

#include <QtCore/QPointer>
#include <QtWidgets/QGraphicsPixmapItem>

#include "src/engine/map/MapCoordinates.hpp"

class Character;

class DynamicElement : public QGraphicsPixmapItem
{
    private:
        const QSizeF& baseTileSize;

    public:
        DynamicElement(const QSizeF& baseTileSize, const QPixmap& elementImage, const MapCoordinates& location);

        void updateLocation(const MapCoordinates& location);
};

#endif // DYNAMICELEMENT_HPP
