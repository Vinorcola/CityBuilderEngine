#ifndef MAPSEARCHENGINE_HPP
#define MAPSEARCHENGINE_HPP

#include <QtCore/QHash>
#include <QtCore/QSet>
#include <QtCore/QString>

#include "src/engine/map/MapCoordinates.hpp"
#include "src/defines.hpp"

class MapArea;
class NatureElementInformation;
class PathGenerator;
class PathInterface;

class MapSearchEngine
{
    private:
        const PathGenerator& pathGenerator;
        QHash<const NatureElementInformation*, QSet<QString>> rawMaterialCoordinates;

    public:
        explicit MapSearchEngine(const PathGenerator& pathGenerator);

        void registerRawMaterial(const NatureElementInformation& conf, const MapArea& area);

        owner<PathInterface*> getPathToClosestRawMaterial(
            const NatureElementInformation& conf,
            const MapCoordinates& origin
        ) const;

    private:
        QString hashCoordinates(const MapCoordinates& coordinates) const;
};

#endif // MAPSEARCHENGINE_HPP
