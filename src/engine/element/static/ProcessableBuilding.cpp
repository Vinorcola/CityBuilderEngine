#include "ProcessableBuilding.hpp"



ProcessableBuilding::ProcessableBuilding(
    QObject* parent,
    const BuildingInformation& conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
):
    Building(parent, conf, area),
    entryPoint(entryPoint),
    viewVersion(0)
{

}



const MapCoordinates& ProcessableBuilding::getEntryPoint() const
{
    return entryPoint;
}



bool ProcessableBuilding::isViewUpToDate(const int currentViewVersion) const
{
    return viewVersion == currentViewVersion;
}



int ProcessableBuilding::getViewVersion() const
{
    return viewVersion;
}



bool ProcessableBuilding::processInteraction(const CycleDate& /*date*/, Character& /*actor*/)
{
    return false;
}



void ProcessableBuilding::notifyViewDataChange()
{
    ++viewVersion;
}
