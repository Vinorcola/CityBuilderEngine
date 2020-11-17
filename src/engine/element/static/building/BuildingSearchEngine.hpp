#ifndef BUILDINGSEARCHENGINE_HPP
#define BUILDINGSEARCHENGINE_HPP

#include <list>

#include "src/engine/element/static/building/AbstractProcessableBuilding.hpp"
#include "src/engine/element/static/building/StorageBuilding.hpp"
#include "src/defines.hpp"

class AbstractProcessableBuilding;
class BuildingInformation;
class ItemInformation;
class MapCoordinates;
class StorageBuilding;

using BuildingList = std::list<Reference<AbstractProcessableBuilding>>;
using StorageBuildingList = std::list<Reference<StorageBuilding>>;

/**
 * @brief A search engine for buildings.
 *
 * Mostly, buildings are search by type. Storage buildings are handled in a specific way because we want to search them
 * by items they can accept.
 *
 * Note for now, the search engine only return the first building registered. It does not take distance into account.
 * This is yet a TODO. Frthermore, we should plan an "item storage search engine" for better performance.
 * StorageBuilding won't be the only building storing items. IndustrialBuildings & CommercialBuildings may also be valid
 * targets to store items.
 */
class BuildingSearchEngine
{
    private:
        QHash<const BuildingInformation*, BuildingList> buildingsPerType;
        StorageBuildingList storageBuildings;

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
