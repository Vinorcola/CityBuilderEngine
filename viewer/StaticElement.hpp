#ifndef STATICELEMENT_HPP
#define STATICELEMENT_HPP

#include <QGraphicsPixmapItem>

#include "engine/map/MapSize.hpp"

class StaticElement : public QGraphicsPixmapItem
{
    private:
        QPainterPath shapePath;

    public:
        StaticElement(const QSizeF& baseTileSize, const MapSize& elementSize, const QPixmap& elementImage);

        virtual QPainterPath shape() const;
};

#endif // STATICELEMENT_HPP
