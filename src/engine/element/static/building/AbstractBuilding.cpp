#include "AbstractBuilding.hpp"



AbstractBuilding::AbstractBuilding(const BuildingInformation& conf, const MapArea& area) :
    conf(conf),
    area(area),
    viewVersion(0)
{

}



const BuildingInformation& AbstractBuilding::getConf() const
{
    return conf;
}



const MapArea& AbstractBuilding::getArea() const
{
    return area;
}



bool AbstractBuilding::isViewUpToDate(const int currentViewVersion) const
{
    return currentViewVersion == viewVersion;
}



int AbstractBuilding::getViewVersion() const
{
    return viewVersion;
}



void AbstractBuilding::notifyViewDataChange()
{
    ++viewVersion;
}
