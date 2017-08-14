#include "BuildingButton.hpp"

#include "global/conf/StaticElementInformation.hpp"



BuildingButton::BuildingButton(const StaticElementInformation* elementConf) :
    QPushButton(elementConf->getTitle()),
    elementConf(elementConf)
{

}



const StaticElementInformation* BuildingButton::getAssociatedBuilding() const
{
    return elementConf;
}
