#ifndef BUILDINGSEARCHENGINE_HPP
#define BUILDINGSEARCHENGINE_HPP

#include "src/defines.hpp"

class AbstractProcessableBuilding;
class BuildingInformation;
class ItemInformation;
class MapCoordinates;
class StorageBuilding;

class BuildingSearchEngine
{
    public:
        BuildingSearchEngine();

        void registerBuilding(AbstractProcessableBuilding& building);
        void registerStorageBuilding(StorageBuilding& building);

        optional<AbstractProcessableBuilding*> findClosestBuilding(
            const BuildingInformation& buildingConf,
            const MapCoordinates& origin
        ) const;
        optional<StorageBuilding*> findClosestStorageThatCanStore(
            const ItemInformation& itemConf,
            const MapCoordinates& origin
        ) const;
};

#endif // BUILDINGSEARCHENGINE_HPP
