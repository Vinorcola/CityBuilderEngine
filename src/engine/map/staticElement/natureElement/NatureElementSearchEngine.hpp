#ifndef NATUREELEMENTSEARCHENGINE_HPP
#define NATUREELEMENTSEARCHENGINE_HPP

#include <QtCore/QHash>
#include <QtCore/QSet>
#include <QtCore/QSharedPointer>
#include <QtCore/QString>

#include "src/defines.hpp"

class NatureElementInformation;
class PathGeneratorInterface;
class PathInterface;
class TileArea;
class TileCoordinates;

using TileCoordinatesList = QSet<QString>;

class NatureElementSearchEngine
{
    private:
        const PathGeneratorInterface& pathGenerator;
        QHash<const NatureElementInformation*, TileCoordinatesList> rawMaterialCoordinates;

    public:
        explicit NatureElementSearchEngine(const PathGeneratorInterface& pathGenerator);

        void registerRawMaterial(const NatureElementInformation& conf, const TileArea& area);

        QSharedPointer<PathInterface> getPathToClosestRawMaterial(
            const NatureElementInformation& conf,
            const TileCoordinates& origin
        ) const;
};

#endif // NATUREELEMENTSEARCHENGINE_HPP
