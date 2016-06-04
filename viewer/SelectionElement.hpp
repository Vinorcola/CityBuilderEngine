#ifndef SELECTIONELEMENT_HPP
#define SELECTIONELEMENT_HPP

#include <QBrush>
#include <QGraphicsPolygonItem>
#include <QPen>

#include "engine/map/MapSize.hpp"





class SelectionElement : public QGraphicsPolygonItem
{
    private:
        QSizeF baseTileSize;
        QBrush goodBrush;
        QPen goodPen;



    public:
        SelectionElement(const QSizeF& baseTileSize);



        void setSize(const MapSize& size);
};

#endif // SELECTIONELEMENT_HPP
