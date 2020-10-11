#include "Building.hpp"



Building::Building(QObject* parent, const BuildingInformation& conf, const MapArea& area) :
    QObject(parent),
    conf(conf),
    area(area),
    viewVersion(0)
{

}



const BuildingInformation& Building::getConf() const
{
    return conf;
}



const MapArea& Building::getArea() const
{
    return area;
}



bool Building::isViewUpToDate(const int currentViewVersion) const
{
    return viewVersion == currentViewVersion;
}



int Building::getViewVersion() const
{
    return viewVersion;
}



void Building::notifyViewDataChange()
{
    ++viewVersion;
}
