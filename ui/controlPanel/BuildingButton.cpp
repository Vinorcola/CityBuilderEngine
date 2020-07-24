#include "BuildingButton.hpp"

#include "global/conf/BuildingInformation.hpp"



BuildingButton::BuildingButton(const BuildingInformation* elementConf) :
    QPushButton(elementConf->getTitle()),
    elementConf(elementConf)
{

}



const BuildingInformation* BuildingButton::getAssociatedBuilding() const
{
    return elementConf;
}
