#include "BuildingButton.hpp"



BuildingButton::BuildingButton(const StaticElementInformation* elementConf) :
    QPushButton(elementConf->getTitle()),
    elementConf(elementConf)
{

}



const StaticElementInformation* BuildingButton::getAssociatedBuilding() const
{
    return elementConf;
}
