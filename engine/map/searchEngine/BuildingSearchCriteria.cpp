#include "BuildingSearchCriteria.hpp"

#include "global/conf/BuildingInformation.hpp"
#include "global/conf/Conf.hpp"



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
