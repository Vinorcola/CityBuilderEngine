#ifndef BUILDINGSEARCHENGINE_HPP
#define BUILDINGSEARCHENGINE_HPP

#include "src/defines.hpp"

class BuildingInformation;
class MapCoordinates;
class ProcessableBuilding;
class StorageBuilding;

class BuildingSearchEngine
{
    public:
        BuildingSearchEngine();

        void registerBuilding(ProcessableBuilding& building);
        void registerStorageBuilding(StorageBuilding& building);

        optional<ProcessableBuilding*> findClosestBuilding(
            const BuildingInformation& buildingConf,
            const MapCoordinates& origin
        ) const;
};

#endif // BUILDINGSEARCHENGINE_HPP
