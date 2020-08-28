#ifndef MAPSEARCHENGINE_HPP
#define MAPSEARCHENGINE_HPP

#include <list>
#include <QtCore/QHash>
#include <QtCore/QPointer>
#include <QtCore/QSet>
#include <QtCore/QString>

#include "src/engine/map/MapCoordinates.hpp"
#include "src/defines.hpp"

class BuildingInformation;
class ItemInformation;
class LaboratoryBuilding;
class MapArea;
class NatureElementInformation;
class PathGenerator;
class PathInterface;
class StorageBuilding;

using LaboratoryList = std::list<QPointer<LaboratoryBuilding>>;

class MapSearchEngine
{
    private:
        const PathGenerator& pathGenerator;
        QHash<const NatureElementInformation*, QSet<QString>> rawMaterialCoordinates;
        std::list<QPointer<StorageBuilding>> storageBuildings;
        QHash<const BuildingInformation*, LaboratoryList> laboratoryBuildings;

    public:
        explicit MapSearchEngine(const PathGenerator& pathGenerator);

        void registerRawMaterial(const NatureElementInformation& conf, const MapArea& area);

        void registerStorageBuilding(StorageBuilding& building);

        void registerLaboratoryBuilding(LaboratoryBuilding& building);

        optional<owner<PathInterface*>> getPathToClosestRawMaterial(
            const NatureElementInformation& conf,
            const MapCoordinates& origin
        ) const;

        optional<StorageBuilding*> getStorageThatCanStore(const ItemInformation& itemConf) const;

        optional<LaboratoryBuilding*> getLaboratory(const BuildingInformation& buildingConf) const;

    private:
        QString hashCoordinates(const MapCoordinates& coordinates) const;
};

#endif // MAPSEARCHENGINE_HPP
