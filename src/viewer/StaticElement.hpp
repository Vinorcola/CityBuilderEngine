#ifndef STATICELEMENT_HPP
#define STATICELEMENT_HPP

#include <QtWidgets/QGraphicsPixmapItem>

#include "src/engine/map/MapSize.hpp"

class StaticElement : public QGraphicsPixmapItem
{
    private:
        QPainterPath shapePath;

    public:
        StaticElement(const QSizeF& baseTileSize, const MapSize& elementSize, const QPixmap& elementImage);

        virtual QPainterPath shape() const;
};

#endif // STATICELEMENT_HPP
