#include "MapViewer.hpp"

#include "src/engine/map/Map.hpp"
#include "src/viewer/MapScene.hpp"



MapViewer::MapViewer(const Conf& conf, const Map& map, QWidget* parent) :
    QGraphicsView(parent),
    imageLibrary(conf)
{
    setScene(new MapScene(conf, map, imageLibrary));
}



void MapViewer::buildingRequest(const BuildingInformation& elementConf)
{
    static_cast<MapScene*>(scene())->requestBuildingPositioning(elementConf);
}
