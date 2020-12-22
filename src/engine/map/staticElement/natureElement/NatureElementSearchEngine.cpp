#include "NatureElementSearchEngine.hpp"

#include "src/engine/map/path/PathGeneratorInterface.hpp"
#include "src/engine/map/Tile.hpp"
#include "src/global/geometry/TileArea.hpp"



NatureElementSearchEngine::NatureElementSearchEngine(const PathGeneratorInterface& pathGenerator) :
    pathGenerator(pathGenerator),
    rawMaterialCoordinates()
{

}



void NatureElementSearchEngine::registerRawMaterial(const NatureElementInformation& conf, const TileArea& area)
{
    if (!rawMaterialCoordinates.contains(&conf)) {
        rawMaterialCoordinates[&conf] = {};
    }

    auto& coordinatesSet(rawMaterialCoordinates[&conf]);
    for (auto coordinates : area) {
        coordinatesSet << coordinates.hash();
    }
}



QSharedPointer<PathInterface> NatureElementSearchEngine::getPathToClosestRawMaterial(
    const NatureElementInformation& conf,
    const Tile& origin
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
        [&coordinatesSet](const Tile& tile) {
            return coordinatesSet.contains(tile.coordinates().hash());
        }
    );
}
