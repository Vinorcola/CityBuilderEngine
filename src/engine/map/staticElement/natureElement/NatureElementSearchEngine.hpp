#ifndef NATUREELEMENTSEARCHENGINE_HPP
#define NATUREELEMENTSEARCHENGINE_HPP

#include <QtCore/QHash>
#include <QtCore/QSet>
#include <QtCore/QSharedPointer>
#include <QtCore/QString>

#include "src/defines.hpp"

class MapArea;
class MapCoordinates;
class NatureElementInformation;
class PathInterface;
class PathGeneratorInterface;

using MapCoordinatesList = QSet<QString>;

class NatureElementSearchEngine
{
    private:
        const PathGeneratorInterface& pathGenerator;
        QHash<const NatureElementInformation*, MapCoordinatesList> rawMaterialCoordinates;

    public:
        explicit NatureElementSearchEngine(const PathGeneratorInterface& pathGenerator);

        void registerRawMaterial(const NatureElementInformation& conf, const MapArea& area);

        QSharedPointer<PathInterface> getPathToClosestRawMaterial(
            const NatureElementInformation& conf,
            const MapCoordinates& origin
        ) const;
};

#endif // NATUREELEMENTSEARCHENGINE_HPP
