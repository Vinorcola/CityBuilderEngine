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
};

#endif // MAPSCENE_HPP
