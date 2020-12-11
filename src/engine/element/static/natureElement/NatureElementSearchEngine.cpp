#include "NatureElementSearchEngine.hpp"

#include "src/engine/element/static/path/PathGenerator.hpp"
#include "src/engine/map/MapArea.hpp"



NatureElementSearchEngine::NatureElementSearchEngine(const PathGenerator& pathGenerator) :
    pathGenerator(pathGenerator),
    rawMaterialCoordinates()
{

}



void NatureElementSearchEngine::registerRawMaterial(const NatureElementInformation& conf, const MapArea& area)
{
    if (!rawMaterialCoordinates.contains(&conf)) {
        rawMaterialCoordinates[&conf] = {};
    }

    auto& coordinatesSet(rawMaterialCoordinates[&conf]);
    for (auto coordinates : area) {
        coordinatesSet << coordinates.getHash();
    }
}



optional<owner<PathInterface*>> NatureElementSearchEngine::getPathToClosestRawMaterial(
    const NatureElementInformation& conf,
    const MapCoordinates& origin
) const
{
    if (!rawMaterialCoordinates.contains(&conf)) {
        // No elements of that type registered.
        return nullptr;
    }

    auto& coordinatesSet(rawMaterialCoordinates[&conf]);
    if (coordinatesSet.isEmpty()) {
        // No more elements of that type registered.
        return nullptr;
    }

    return pathGenerator.generateShortestPathToClosestMatch(
        origin,
        [&coordinatesSet](const MapCoordinates& location) {
            return coordinatesSet.contains(location.getHash());
        }
    );
}