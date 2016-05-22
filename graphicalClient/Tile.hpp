#ifndef TILE_HPP
#define TILE_HPP

#include <QStack>

#include "engine/map/MapCoordinates.hpp"
#include "graphicalClient/StaticElementGraphicsItem.hpp"





class Tile : public QGraphicsItem
{
    private:
        MapCoordinates location;
        QStack<StaticElementGraphicsItem*> graphicsItemList;



    public:
        Tile(const MapCoordinates& location, const QSizeF& baseTileSize);



        const MapCoordinates& getCoordinates() const;



        void pushGraphicsItem(StaticElementGraphicsItem* graphicsItem);



        /**
         * @brief Pop the last graphics item displayed the tile.
         *
         * The graphics item's parent is reset so make sure you delete the object if you don't use it anymore.
         */
        StaticElementGraphicsItem* popGraphicsItem();



        virtual QRectF boundingRect() const;
        virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);
};

#endif // TILE_HPP
