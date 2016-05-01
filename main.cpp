#include <QCoreApplication>

#include "engine/buildings/MaintenanceBuilding.hpp"
#include "engine/Map.hpp"





int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    
    Map map({ 30, 30 });
    
    MaintenanceBuilding* building1(new MaintenanceBuilding({ 10, 10 }));
    map.registerProcessable(building1);
    
    return a.exec();
}
