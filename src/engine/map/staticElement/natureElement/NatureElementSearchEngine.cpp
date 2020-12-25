#include "NatureElementSearchEngine.hpp"

#include "src/engine/map/path/PathGeneratorInterface.hpp"
#include "src/engine/map/staticElement/natureElement/NatureElement.hpp"
#include "src/engine/map/Tile.hpp"
#include "src/global/geometry/TileArea.hpp"



NatureElementSearchEngine::NatureElementSearchEngine(const PathGeneratorInterface& pathGenerator) :
    pathGenerator(pathGenerator),
    availableNaturalResources()
{

}



void NatureElementSearchEngine::registerNaturalResource(const QSharedPointer<NatureElement>& naturalResource)
{
    auto& conf(naturalResource->getConf());
    if (!availableNaturalResources.contains(&conf)) {
        availableNaturalResources[&conf] = {};
    }

    auto& naturalRessources(availableNaturalResources[&conf]);
    for (auto coordinates : naturalResource->getArea()) {
        naturalRessources.insert(coordinates.hash(), naturalResource);
    }
}



QSharedPointer<PathInterface> NatureElementSearchEngine::getPathToClosestNaturalResource(
    const NatureElementInformation& conf,
    const Tile& origin
) const
{
    if (!availableNaturalResources.contains(&conf)) {
        // No elements of that type registered.
        return {};
    }

    auto& coordinatesSet(availableNaturalResources[&conf]);
    if (coordinatesSet.isEmpty()) {
        // No more elements of that type registered.
        return {};
    }

    return pathGenerator.generateShortestPathToClosestMatch(
        origin,
        [&coordinatesSet](const Tile& tile) -> QWeakPointer<AbstractStaticElement> {
            auto naturalResource(coordinatesSet.value(tile.coordinates().hash()).toStrongRef());
            if (naturalResource.isNull() || naturalResource->isBusy()) {
                return {};
            }

            return naturalResource;
        }
    );
}
