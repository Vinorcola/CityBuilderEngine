#include "BuildingSearchEngine.hpp"

#include "src/engine/map/staticElement/building/AbstractStoringBuilding.hpp"



BuildingSearchEngine::BuildingSearchEngine() :
    buildingsPerType(),
    storingBuildings()
{

}



void BuildingSearchEngine::registerBuilding(const QSharedPointer<AbstractProcessableBuilding>& building)
{
    auto key(&building->getConf());
    if (!buildingsPerType.contains(key)) {
        buildingsPerType.insert(key, {});
    }

    buildingsPerType[key].append(building);
}



void BuildingSearchEngine::registerStoringBuilding(const QSharedPointer<AbstractStoringBuilding>& building)
{
    storingBuildings.append(building);
}



QSharedPointer<optional<AbstractProcessableBuilding>> BuildingSearchEngine::findClosestBuilding(
    const BuildingInformation& buildingConf,
    const Tile& /*origin*/
) const {

    if (!buildingsPerType.contains(&buildingConf)) {
        return nullptr;
    }

    // For now, we return the first laboratory. To review.
    for (auto& buildingRef : buildingsPerType[&buildingConf]) {
        auto building(buildingRef.toStrongRef());
        if (building) {
            return building;
        }
    }

    return nullptr;
}



QSharedPointer<optional<AbstractStoringBuilding> > BuildingSearchEngine::findClosestStorageThatCanStore(
    const ItemInformation& itemConf,
    const Tile& /*origin*/
) const {

    for (auto& buildingRef : storingBuildings) {
        auto building(buildingRef.toStrongRef());
        if (building && building->storableQuantity(itemConf) > 0) {
            return building;
        }
    }

    return nullptr;
}
