#include "MapSearchEngine.hpp"

#include "src/engine/map/path/PathGenerator.hpp"
#include "src/engine/map/MapArea.hpp"
#include "src/global/conf/NatureElementInformation.hpp"



MapSearchEngine::MapSearchEngine(const PathGenerator& pathGenerator) :
    pathGenerator(pathGenerator),
    rawMaterialCoordinates()
{

}



void MapSearchEngine::registerRawMaterial(const NatureElementInformation& conf, const MapArea& area)
{
    auto coordinatesSet(rawMaterialCoordinates[&conf]);
    for (auto coordinates : area) {
        coordinatesSet << hashCoordinates(coordinates);
    }
}



owner<PathInterface*> MapSearchEngine::getPathToClosestRawMaterial(
    const NatureElementInformation& conf,
    const MapCoordinates& origin
) const {

    auto coordinatesSet(rawMaterialCoordinates[&conf]);

    return pathGenerator.generateShortestPathToClosestMatch(
        origin,
        [this, &coordinatesSet](const MapCoordinates& location) {
            return coordinatesSet.contains(hashCoordinates(location));
        }
    );
}



QString MapSearchEngine::hashCoordinates(const MapCoordinates& coordinates) const
{
    return QString::number(coordinates.getX()) + ';' + QString::number(coordinates.getY());
}
