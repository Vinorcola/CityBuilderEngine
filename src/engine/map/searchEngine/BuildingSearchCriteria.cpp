#include "BuildingSearchCriteria.hpp"

#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/Conf.hpp"



BuildingSearchCriteria::BuildingSearchCriteria(
    const QList<const BuildingInformation *>& allowedBuildingTypes,
    const ItemInformation* acceptingItem
) :
    allowedBuildingTypes(allowedBuildingTypes),
    acceptingItem(acceptingItem)
{

}



const QList<const BuildingInformation*>& BuildingSearchCriteria::getAllowedBuildingTypes() const
{
    return allowedBuildingTypes;
}



const ItemInformation *BuildingSearchCriteria::getAcceptingItem() const
{
    return acceptingItem;
}
