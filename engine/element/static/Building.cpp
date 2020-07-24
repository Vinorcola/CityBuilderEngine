#include "Building.hpp"



Building::Building(QObject* parent, const StaticElementInformation* conf, const MapArea& area) :
    QObject(parent),
    conf(conf),
    area(area)
{

}



const StaticElementInformation*Building::getConf() const
{
    return conf;
}



const MapArea& Building::getArea() const
{
    return area;
}
