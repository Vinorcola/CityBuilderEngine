#include "BuildingSearchEngine.hpp"



BuildingSearchEngine::BuildingSearchEngine() :
    buildingsPerType(),
    storageBuildings()
{

}



void BuildingSearchEngine::registerBuilding(AbstractProcessableBuilding& building)
{
    auto key(&building.getConf());
    if (!buildingsPerType.contains(key)) {
        buildingsPerType.insert(key, {});
    }

    buildingsPerType[key].append(building);
}



void BuildingSearchEngine::registerStorageBuilding(StorageBuilding& building)
{
    storageBuildings.append(building);
}



optional<AbstractProcessableBuilding*> BuildingSearchEngine::findClosestBuilding(
    const BuildingInformation& buildingConf,
    const MapCoordinates& /*origin*/
) const {

    if (!buildingsPerType.contains(&buildingConf)) {
        return nullptr;
    }

    // For now, we return the first laboratory. To review.
    for (auto building : buildingsPerType[&buildingConf]) {
        if (building.isValid()) {
            return &building.get();
        }
    }

    return nullptr;
}



optional<StorageBuilding*> BuildingSearchEngine::findClosestStorageThatCanStore(
    const ItemInformation& itemConf,
    const MapCoordinates& /*origin*/
) const {

    for (auto building : storageBuildings) {
        if (building.isValid() && building.get().storableQuantity(itemConf) > 0) {
            return &building.get();
        }
    }

    return nullptr;
}
