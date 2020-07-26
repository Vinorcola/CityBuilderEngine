#include "Building.hpp"



Building::Building(QObject* parent, const BuildingInformation* conf, const MapArea& area) :
    QObject(parent),
    conf(conf),
    area(area)
{

}



const BuildingInformation*Building::getConf() const
{
    return conf;
}



const MapArea& Building::getArea() const
{
    return area;
}
