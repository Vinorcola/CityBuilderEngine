#include <QCoreApplication>

#include "engine/buildings/MaintenanceBuilding.hpp"
#include "engine/Map.hpp"





int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    
    Map map({ 30, 30 });
    
    new MaintenanceBuilding(&map, { 0, 10 });
    
    return a.exec();
}
