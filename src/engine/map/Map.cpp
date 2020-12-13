#include "Map.hpp"

#include "src/engine/loader/CityLoader.hpp"
#include "src/engine/map/MapArea.hpp"
#include "src/engine/map/MapCoordinates.hpp"
#include "src/engine/state/MapState.hpp"
#include "src/global/conf/Conf.hpp"



Map::Map(
    const Conf& conf,
    CityLoader& loader,
    PopulationRegistryInterface& populationRegistry,
    WorkingPlaceRegistryInterface& workingPlaceRegistry
) :
    size(loader.getMapSize()),
    civilianEntryPoint(CivilianEntryPoint::Create(
        dynamicElements,
        conf.getBuildingConf("mapEntryPoint"),
        loader.getMapEntryPoint(),
        conf.getCharacterConf("immigrant")
    )),
    pathGenerator(*this),
    staticElements(dynamicElements, populationRegistry, workingPlaceRegistry, pathGenerator, *civilianEntryPoint.get()),
    dynamicElements(pathGenerator, staticElements.getBuildingSearchEngine())
{

}



MapState Map::getState() const
{
    return MapState(size);
}




bool Map::isLocationValid(const MapCoordinates& coordinates) const
{
    int sum(coordinates.getY() + coordinates.getX());
    int diff(coordinates.getY() - coordinates.getX());
    return (
        diff >= 0 && diff < size.height() &&
        sum >= 0 && sum <= size.width()
    );
}



bool Map::isAreaValid(const MapArea& area) const
{
    return (
        isLocationValid(area.getLeft()) &&
        isLocationValid(area.getRight()) &&
        isLocationValid(area.getTop()) &&
        isLocationValid(area.getBottom())
    );
}



bool Map::isLocationTraversable(const MapCoordinates& location) const
{
    // TODO
}



bool Map::hasRoadAtLocation(const MapCoordinates& location) const
{
    // TODO
}



bool Map::canConstructRoadAtLocation(const MapCoordinates& location) const
{
    // TODO
}
