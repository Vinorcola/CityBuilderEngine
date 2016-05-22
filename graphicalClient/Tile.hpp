#ifndef TILE_HPP
#define TILE_HPP

#include <QStack>

#include "engine/map/MapCoordinates.hpp"
#include "graphicalClient/StaticElementGraphicsItem.hpp"





class Tile : public QObject
{
        Q_OBJECT


    private:
        MapCoordinates location;
        QPointF graphicalAttachPoint;
        QStack<StaticElementGraphicsItem*> graphicsItemlist;



    public:
        Tile(const MapCoordinates& location, const QSizeF& baseTileSize, QObject* parent);



        void pushGraphicsItem(StaticElementGraphicsItem* graphicsItem);



        StaticElementGraphicsItem* popGraphicsItem();
};

#endif // TILE_HPP
