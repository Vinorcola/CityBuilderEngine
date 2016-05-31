#include <QApplication>
#include <QDateTime>

#include "engine/element/building/MaintenanceBuilding.hpp"
#include "engine/element/building/Road.hpp"
#include "engine/map/Map.hpp"
#include "graphicalClient/MapViewer.hpp"





int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    qsrand(QDateTime::currentDateTime().toTime_t());
    
    Map map({ 23, 33 });

    MapViewer* window(new MapViewer(map));
    window->show();

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
    map.createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(3, 10), MapSize(1)));
    map.createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(4, 10), MapSize(1)));
    map.createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(5, 10), MapSize(1)));
    map.createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(6, 10), MapSize(1)));
    map.createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(7, 10), MapSize(1)));
    map.createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(2, 10), MapSize(1)));
    map.createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(1, 10), MapSize(1)));
    map.createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(0, 10), MapSize(1)));
    map.createStaticElement(Map::StaticElementType::Road, MapArea(MapCoordinates(-4, 12), MapSize(1)));

    // Buildings
    map.createStaticElement(Map::StaticElementType::Maintenance, MapArea(MapCoordinates(1, 5), MapSize(2)));
    
    return a.exec();
}
