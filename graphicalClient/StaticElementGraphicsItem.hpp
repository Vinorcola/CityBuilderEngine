#ifndef STATICELEMENTGRAPHICSITEM_HPP
#define STATICELEMENTGRAPHICSITEM_HPP

#include <QGraphicsPixmapItem>

#include "engine/map/MapSize.hpp"





class StaticElementGraphicsItem : public QGraphicsPixmapItem
{
    private:
        QPainterPath shapePath;



    public:
        StaticElementGraphicsItem(const QSizeF& baseTileSize, const MapSize& elementSize, const QPixmap& elementImage);



        virtual QPainterPath shape() const;
};

#endif // STATICELEMENTGRAPHICSITEM_HPP
