#include "MapSearchEngine.hpp"

#include "src/engine/element/static/building/LaboratoryBuilding.hpp"
#include "src/engine/element/static/building/StorageBuilding.hpp"
#include "src/engine/map/path/PathGenerator.hpp"
#include "src/engine/map/MapArea.hpp"
#include "src/global/conf/NatureElementInformation.hpp"



MapSearchEngine::MapSearchEngine(const PathGenerator& pathGenerator) :
    pathGenerator(pathGenerator),
    rawMaterialCoordinates(),
    storageBuildings(),
    laboratoryBuildings()
{

}



void MapSearchEngine::registerRawMaterial(const NatureElementInformation& conf, const MapArea& area)
{
    if (!rawMaterialCoordinates.contains(&conf)) {
        rawMaterialCoordinates[&conf] = {};
    }

    auto& coordinatesSet(rawMaterialCoordinates[&conf]);
    for (auto coordinates : area) {
        coordinatesSet << hashCoordinates(coordinates);
    }
}



void MapSearchEngine::registerStorageBuilding(StorageBuilding& building)
{
    storageBuildings.push_back(&building);
}



void MapSearchEngine::registerLaboratoryBuilding(LaboratoryBuilding& building)
{
    auto key(&building.getConf());
    if (!laboratoryBuildings.contains(key)) {
        laboratoryBuildings.insert(key, {});
    }

    laboratoryBuildings[key].push_back(&building);
}



optional<owner<PathInterface*>> MapSearchEngine::getPathToClosestRawMaterial(
    const NatureElementInformation& conf,
    const MapCoordinates& origin
) const {

    if (!rawMaterialCoordinates.contains(&conf)) {
        // No elements of that type registered.
        return nullptr;
    }

    auto& coordinatesSet(rawMaterialCoordinates[&conf]);
    if (coordinatesSet.isEmpty()) {
        // No more elements of that type registered.
        return nullptr;
    }

    return pathGenerator.generateShortestPathToClosestMatch(
        origin,
        [this, &coordinatesSet](const MapCoordinates& location) {
            return coordinatesSet.contains(hashCoordinates(location));
        }
    );
}



optional<StorageBuilding*> MapSearchEngine::getStorageThatCanStore(const ItemInformation& itemConf) const
{
    for (auto building : storageBuildings) {
        if (building->storableQuantity(itemConf) > 0) {
            return building;
        }
    }

    return nullptr;
}



optional<LaboratoryBuilding*> MapSearchEngine::getLaboratory(const BuildingInformation& buildingConf) const
{
    if (!laboratoryBuildings.contains(&buildingConf)) {
        return nullptr;
    }

    if (laboratoryBuildings[&buildingConf].size() == 0) {
        return nullptr;
    }

    // For now, we return the first laboratory. To review.
    return laboratoryBuildings[&buildingConf].front();
}



QString MapSearchEngine::hashCoordinates(const MapCoordinates& coordinates) const
{
    return QString::number(coordinates.getX()) + ';' + QString::number(coordinates.getY());
}
