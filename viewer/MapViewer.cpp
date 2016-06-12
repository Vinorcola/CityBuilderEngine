#include "MapViewer.hpp"

#include "viewer/MapScene.hpp"





MapViewer::MapViewer(Map& map, QWidget* parent) :
    QGraphicsView(parent)
{
    setScene(new MapScene(map));
}





void MapViewer::buildingRequest(Map::StaticElementType type)
{
    static_cast<MapScene*>(scene())->requestBuilding(type);
}





void MapViewer::cancelBuildingRequest()
{
    static_cast<MapScene*>(scene())->cancelBuildingRequest();
}
