#include "SearchEngine.hpp"

#include "engine/element/static/Building.hpp"
#include "engine/element/static/ProcessableBuilding.hpp"
#include "engine/map/searchEngine/BuildingSearchCriteria.hpp"



SearchEngine::SearchEngine(QObject* parent, const QLinkedList<Building*>& buildingList) :
    QObject(parent),
    buildingList(buildingList)
{

}



QList<Building*> SearchEngine::search(const BuildingSearchCriteria& criteria) const
{
    QList<Building*> results;
    for (auto building : buildingList) {
        if (!isBuildingTypeAllowedByCriteria(building->getConf(), criteria)) {
            continue;
        }
        if (!canBuildingAcceptCarriedItem(building, criteria)) {
            continue;
        }

        results.append(building);
    }

    return results;
}



bool SearchEngine::isBuildingTypeAllowedByCriteria(
    const BuildingInformation* buildingType,
    const BuildingSearchCriteria& criteria
) const {

    for (auto allowedBuilding : criteria.getAllowedBuildingTypes()) {
        if (allowedBuilding == buildingType) {
            return true;
        }
    }

    return false;
}



bool SearchEngine::canBuildingAcceptCarriedItem(const Building* building, const BuildingSearchCriteria& criteria) const
{
    auto item(criteria.getAcceptingItem());
    if (item == nullptr) {
        // No items carried, we always accept.
        return true;
    }

    auto processableBuilding(dynamic_cast<const ProcessableBuilding*>(building));
    if (!processableBuilding) {
        return false;
    }

    return processableBuilding->acceptItem(item);
}
