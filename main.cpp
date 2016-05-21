#include <QCoreApplication>
#include <QDateTime>

#include "engine/element/building/MaintenanceBuilding.hpp"
#include "engine/element/building/Road.hpp"
#include "engine/map/Map.hpp"





int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    qsrand(QDateTime::currentDateTime().toTime_t());
    
    Map map({ 30, 30 });

    // Roads
    map.createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(3, 4), MapSize(1)));
    map.createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(2, 4), MapSize(1)));
    map.createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(1, 4), MapSize(1)));
    map.createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(0, 4), MapSize(1)));
    map.createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(3, 5), MapSize(1)));
    map.createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(4, 5), MapSize(1)));
    map.createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(5, 5), MapSize(1)));
    map.createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(3, 6), MapSize(1)));
    map.createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(3, 7), MapSize(1)));
    map.createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(3, 8), MapSize(1)));
    map.createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(3, 9), MapSize(1)));

    // Buildings
    map.createStaticElement(Map::StaticElementType::Maintenance, MapArea(MapCoordinates(1, 5), MapSize(2)));
    
    return a.exec();
}
