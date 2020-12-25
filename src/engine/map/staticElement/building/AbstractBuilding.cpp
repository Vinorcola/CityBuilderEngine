#include "AbstractBuilding.hpp"

#include "src/global/state/BuildingState.hpp"



AbstractBuilding::AbstractBuilding(const BuildingInformation& conf, const TileArea& area, Direction orientation) :
    AbstractStaticElement(),
    conf(conf),
    area(area),
    orientation(orientation),
    stateVersion(0)
{

}



AbstractBuilding::~AbstractBuilding()
{

}



const BuildingInformation& AbstractBuilding::getConf() const
{
    return conf;
}



BuildingState AbstractBuilding::getCurrentState() const
{
    return { reinterpret_cast<qintptr>(this), conf, area, orientation, BuildingStatus::Inactive, 0, stateVersion };
}



void AbstractBuilding::notifyViewDataChange()
{
    ++stateVersion;
}
