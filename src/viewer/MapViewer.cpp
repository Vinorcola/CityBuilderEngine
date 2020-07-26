#include "MapViewer.hpp"

#include "src/viewer/MapScene.hpp"



MapViewer::MapViewer(Map& map, QWidget* parent) :
    QGraphicsView(parent)
{
    setScene(new MapScene(map));
}



void MapViewer::buildingRequest(const BuildingInformation* elementConf)
{
    static_cast<MapScene*>(scene())->requestBuildingPositioning(elementConf);
}
