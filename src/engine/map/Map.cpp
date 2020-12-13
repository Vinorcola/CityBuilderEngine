#include "Map.hpp"

#include <QtCore/QDebug>

#include "src/engine/loader/CityLoader.hpp"
#include "src/engine/map/MapArea.hpp"
#include "src/engine/map/MapCoordinates.hpp"
#include "src/engine/processing/CycleDate.hpp"
#include "src/engine/state/MapState.hpp"
#include "src/global/conf/BuildingInformation.hpp"
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



const PathGenerator& Map::getPathGenerator() const
{
    return pathGenerator;
}



MapState Map::getState() const
{
    return MapState(size);
}



QList<BuildingState> Map::getBuildingsState() const
{
    return staticElements.getBuildingsState();
}



QList<NatureElementState> Map::getNatureElementsState() const
{
    return staticElements.getNatureElementsState();
}



QList<CharacterState> Map::getCharactersState() const
{
    return dynamicElements.getCharactersState();
}



void Map::createBuilding(const BuildingInformation& conf, const MapCoordinates& leftCorner, Direction orientation)
{
    MapArea area(leftCorner, conf.getSize(orientation));
    if (!isAreaConstructible(area)) {
        qDebug() << "WARNING: Try to create a building on an occupied area " + area.toString() + ". Skipping the creation.";
        return;
    }

    if (conf.getType() == BuildingInformation::Type::Road) {
        staticElements.generateBuilding(conf, area, orientation);
    }
    else {
        MapCoordinates entryPoint; // TODO
        staticElements.generateProcessableBuilding(conf, area, orientation, entryPoint);
    }

    // TODO: Register in details cache.
}



void Map::createNatureElement(const NatureElementInformation& conf, const MapArea& area)
{
    staticElements.generateNatureElement(conf, area);

    // TODO: Register in details cache.
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



bool Map::isAreaConstructible(const MapArea& area) const
{
    // TODO
    return true;
}



bool Map::isLocationTraversable(const MapCoordinates& location) const
{
    // TODO
    return true;
}



bool Map::hasRoadAtLocation(const MapCoordinates& location) const
{
    // TODO
    return true;
}



bool Map::canConstructRoadAtLocation(const MapCoordinates& location) const
{
    // TODO
    return true;
}



void Map::process(const CycleDate& date)
{
    // Note: order is important: dynamic elements, entry points & static elements.
    dynamicElements.process(date);
    civilianEntryPoint->process(date);
    if (date.isBuildingCycle()) {
        staticElements.process(date);
    }
}
