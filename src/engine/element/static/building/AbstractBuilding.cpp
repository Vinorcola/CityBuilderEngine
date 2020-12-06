#include "AbstractBuilding.hpp"

#include "src/engine/state/BuildingState.hpp"



AbstractBuilding::AbstractBuilding(const BuildingInformation& conf, const MapArea& area, Direction orientation) :
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
    return { reinterpret_cast<qintptr>(this), conf, area, orientation, BuildingState::Status::Inactive, 0, stateVersion };
}



void AbstractBuilding::notifyViewDataChange()
{
    ++stateVersion;
}
