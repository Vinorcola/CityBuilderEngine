#ifndef MAPSCENE_HPP
#define MAPSCENE_HPP

#include <QGraphicsScene>

#include "engine/map/Map.hpp"
#include "viewer/DynamicElement.hpp"
#include "viewer/SelectionElement.hpp"
#include "viewer/Tile.hpp"





class MapScene : public QGraphicsScene
{
        Q_OBJECT


    private:
        QList<Tile*> tileList;
        QList<DynamicElement*> dynamicElementList;
        SelectionElement* selectionElement;



    public:
        MapScene(const Map& map);



        void requestBuilding(Map::StaticElementType type);



        void cancelBuildingRequest();



    public slots:
        void registerNewStaticElement(const QWeakPointer<AbstractStaticMapElement>& element);



        void registerNewDynamicElement(const QWeakPointer<AbstractDynamicMapElement>& element);



        void refresh();



    private:
        Tile* getTileAt(const MapCoordinates& location);



        void addStaticElementBuilding(Tile* tile, const MapSize& elementSize, const QPixmap& elementImage);



    private slots:
        void currentTileChanged(Tile* currentTile);
};

#endif // MAPSCENE_HPP
