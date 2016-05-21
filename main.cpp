#include <QCoreApplication>

#include "engine/element/building/MaintenanceBuilding.hpp"
#include "engine/element/building/Road.hpp"
#include "engine/map/Map.hpp"





int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    
    Map map({ 30, 30 });
    
    new Road(map, MapCoordinates(1, 4));
    new Road(map, MapCoordinates(0, 4));
    AbstractBuilding* building(new MaintenanceBuilding(map, MapArea(MapCoordinates(1, 5), MapSize(2))));
    
    return a.exec();
}
