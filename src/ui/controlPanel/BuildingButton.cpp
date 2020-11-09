#include "BuildingButton.hpp"

#include "src/global/conf/BuildingInformation.hpp"



BuildingButton::BuildingButton(const QString& title, const BuildingInformation& elementConf) :
    QPushButton(title),
    elementConf(elementConf)
{

}



const BuildingInformation& BuildingButton::getAssociatedBuilding() const
{
    return elementConf;
}
