#ifndef MAPSEARCHENGINE_HPP
#define MAPSEARCHENGINE_HPP

#include <list>
#include <QtCore/QHash>
#include <QtCore/QPointer>
#include <QtCore/QSet>
#include <QtCore/QString>

#include "src/engine/map/MapCoordinates.hpp"
#include "src/defines.hpp"

class ItemInformation;
class MapArea;
class NatureElementInformation;
class PathGenerator;
class PathInterface;
class StorageBuilding;

class MapSearchEngine
{
    private:
        const PathGenerator& pathGenerator;
        QHash<const NatureElementInformation*, QSet<QString>> rawMaterialCoordinates;
        std::list<QPointer<StorageBuilding>> storageBuildings;

    public:
        explicit MapSearchEngine(const PathGenerator& pathGenerator);

        void registerRawMaterial(const NatureElementInformation& conf, const MapArea& area);

        void registerStorageBuilding(StorageBuilding& building);

        optional<owner<PathInterface*>> getPathToClosestRawMaterial(
            const NatureElementInformation& conf,
            const MapCoordinates& origin
        ) const;

        optional<StorageBuilding*> getStorageThatCanStore(const ItemInformation& itemConf) const;

    private:
        QString hashCoordinates(const MapCoordinates& coordinates) const;
};

#endif // MAPSEARCHENGINE_HPP
