#ifndef BUILDINGSEARCHENGINE_HPP
#define BUILDINGSEARCHENGINE_HPP

#include "src/engine/map/staticElement/building/AbstractProcessableBuilding.hpp"
#include "src/engine/map/staticElement/building/StorageBuilding.hpp"
#include "src/defines.hpp"

class AbstractProcessableBuilding;
class BuildingInformation;
class ItemInformation;
class StorageBuilding;
class TileCoordinates;

using BuildingList = QList<QWeakPointer<AbstractProcessableBuilding>>;
using StorageBuildingList = QList<QWeakPointer<StorageBuilding>>;

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

        void registerBuilding(const QSharedPointer<AbstractProcessableBuilding>& building);
        void registerStorageBuilding(const QSharedPointer<StorageBuilding>& building);

        QSharedPointer<optional<AbstractProcessableBuilding>> findClosestBuilding(
            const BuildingInformation& buildingConf,
            const Tile& origin
        ) const;
        QSharedPointer<optional<StorageBuilding>> findClosestStorageThatCanStore(
            const ItemInformation& itemConf,
            const Tile& origin
        ) const;
};

#endif // BUILDINGSEARCHENGINE_HPP
