#ifndef STATICELEMENTGRAPHICSITEM_HPP
#define STATICELEMENTGRAPHICSITEM_HPP

#include <QGraphicsPixmapItem>

#include "engine/map/MapSize.hpp"





class StaticElementGraphicsItem : public QGraphicsItem
{
    private:
        QPainterPath shapePath;
        QGraphicsPixmapItem* imageGraphicsItem;



    public:
        StaticElementGraphicsItem(const QSizeF& baseTileSize, const MapSize& elementSize, const QPixmap& elementImage);



        virtual QRectF boundingRect() const;
        virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
        virtual QPainterPath shape() const;
};

#endif // STATICELEMENTGRAPHICSITEM_HPP
