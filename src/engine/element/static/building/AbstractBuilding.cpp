#include "AbstractBuilding.hpp"

#include "src/engine/state/BuildingState.hpp"



AbstractBuilding::AbstractBuilding(const BuildingInformation& conf, const MapArea& area) :
    conf(conf),
    area(area),
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
    return { reinterpret_cast<qintptr>(this), conf, area, BuildingState::Status::Inactive, 0, stateVersion };
}



void AbstractBuilding::notifyViewDataChange()
{
    ++stateVersion;
}
