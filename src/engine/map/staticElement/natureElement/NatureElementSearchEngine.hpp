#ifndef NATUREELEMENTSEARCHENGINE_HPP
#define NATUREELEMENTSEARCHENGINE_HPP

#include <QtCore/QHash>
#include <QtCore/QSharedPointer>
#include <QtCore/QString>
#include <QtCore/QWeakPointer>

#include "src/defines.hpp"

class NatureElement;
class NatureElementInformation;
class PathGeneratorInterface;
class PathInterface;
class Tile;
class TileArea;

using NaturalResourceElements = QHash<QString, QWeakPointer<NatureElement>>;

class NatureElementSearchEngine
{
    private:
        const PathGeneratorInterface& pathGenerator;
        QHash<const NatureElementInformation*, NaturalResourceElements> availableNaturalResources;

    public:
        explicit NatureElementSearchEngine(const PathGeneratorInterface& pathGenerator);

        void registerNaturalResource(const QSharedPointer<NatureElement>& naturalResource);

        QSharedPointer<PathInterface> getPathToClosestNaturalResource(
            const NatureElementInformation& conf,
            const Tile& origin
        ) const;
};

#endif // NATUREELEMENTSEARCHENGINE_HPP
