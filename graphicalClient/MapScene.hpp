#ifndef MAPSCENE_HPP
#define MAPSCENE_HPP

#include <QGraphicsScene>

#include "engine/map/Map.hpp"
#include "graphicalClient/Tile.hpp"





class MapScene : public QGraphicsScene
{
        Q_OBJECT


    private:
        QList<Tile*> tileList;



    public:
        MapScene(const Map& map);



    private:
        Tile* getTileAt(const MapCoordinates& location);



        void addStaticElementBuilding(Tile* tile, const MapSize& elementSize, const QPixmap& elementImage);
};

#endif // MAPSCENE_HPP
