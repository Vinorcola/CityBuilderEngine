#ifndef MAPSCENE_HPP
#define MAPSCENE_HPP

#include <QGraphicsScene>

#include "engine/map/Map.hpp"
#include "graphicalClient/DynamicElement.hpp"
#include "graphicalClient/Tile.hpp"





class MapScene : public QGraphicsScene
{
        Q_OBJECT


    private:
        QList<Tile*> tileList;
        QList<DynamicElement*> dynamicElementList;



    public:
        MapScene(const Map& map);



    public slots:
        void registerNewStaticElement(const QWeakPointer<AbstractStaticMapElement>& element);



        void registerNewDynamicElement(const QWeakPointer<AbstractDynamicMapElement>& element);



        void refresh();



    private:
        Tile* getTileAt(const MapCoordinates& location);



        void addStaticElementBuilding(Tile* tile, const MapSize& elementSize, const QPixmap& elementImage);
};

#endif // MAPSCENE_HPP
