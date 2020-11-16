#include "BuildingSearchEngine.hpp"



BuildingSearchEngine::BuildingSearchEngine()
{

}



void BuildingSearchEngine::registerBuilding(AbstractProcessableBuilding& building)
{

}



void BuildingSearchEngine::registerStorageBuilding(StorageBuilding& building)
{

}



optional<AbstractProcessableBuilding*> BuildingSearchEngine::findClosestBuilding(
    const BuildingInformation& buildingConf,
    const MapCoordinates& origin
) const {

}



optional<StorageBuilding*> BuildingSearchEngine::findClosestStorageThatCanStore(
    const ItemInformation& itemConf,
    const MapCoordinates& origin
) const {

}
