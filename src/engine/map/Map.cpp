#include "Map.hpp"

#include <QtCore/QDebug>

#include "src/engine/loader/CityLoader.hpp"
#include "src/engine/map/Tile.hpp"
#include "src/engine/processing/CycleDate.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/Conf.hpp"
#include "src/global/conf/NatureElementInformation.hpp"



Map::Map(
    const Conf& conf,
    CityLoader& loader,
    PopulationRegistryInterface& populationRegistry,
    WorkingPlaceRegistryInterface& workingPlaceRegistry
) :
    size(loader.getMapSize()),
    tiles(),
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
    // Create the tiles and their graphics item.
    int line(0);
    int column(0);
    while (line < size.height()) {
        // NOTE: Because we divide by 2 and casting as integer, we deliberately remove floating precision. However, the
        // adjustment needs to be 1 higher when "mapSize.width() - line" become negative. This is because -0.5 is cast
        // to 0 insted of -1.
        int adjust(line > size.width() ? 1 : 2);
        while (column < (size.width() - line + adjust) / 2) {
            auto tile(new Tile(column, line + column));
            tiles.insert(tile->getHash(), tile);

            ++column;
        }
        ++line;
        column = -line / 2;
    }
    for (auto tile : tiles) {
        tile->pickRelatives(tiles);
    }
}



Map::~Map()
{
    qDeleteAll(tiles);
}



QList<TileCoordinates> Map::getShortestPathForRoad(const TileCoordinates& origin, const TileCoordinates& target) const
{
    return pathGenerator.generateShortestPathForRoad(origin, target);
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



void Map::createBuilding(const BuildingInformation& conf, const TileCoordinates& leftCorner, Direction orientation)
{
    TileArea area(leftCorner, conf.getSize(orientation));
    if (!isAreaConstructible(area)) {
        qDebug() << "WARNING: Try to create a building on an occupied area " + area.toString() + ". Skipping the creation.";
        return;
    }

    if (conf.getType() == BuildingInformation::Type::Road) {
        staticElements.generateBuilding(conf, area, orientation);
    }
    else {
        staticElements.generateProcessableBuilding(conf, area, orientation, getBestBuildingEntryPoint(area));
    }

    for (auto location : area) {
        tiles.value(location.hash())->registerBuildingConstruction(conf);
    }
}



void Map::createNatureElement(const NatureElementInformation& conf, const TileArea& area)
{
    staticElements.generateNatureElement(conf, area);
    for (auto location : area) {
        tiles.value(location.hash())->registerNatureElement(conf);
    }
}



bool Map::isLocationValid(const TileCoordinates& coordinates) const
{
    return tiles.contains(coordinates.hash());
}



bool Map::isAreaValid(const TileArea& area) const
{
    auto size(area.size());
    if (size.isSquare() && size.height() == 1) {
        return isLocationValid(area.leftCorner());
    }

    return (
        isLocationValid(area.leftCorner()) &&
        isLocationValid(area.resolveRightCorner()) &&
        isLocationValid(area.resolveTopCorner()) &&
        isLocationValid(area.resolveBottomCorner())
    );
}



bool Map::isAreaConstructible(const TileArea& area) const
{
    if (!isAreaValid(area)) {
        return false;
    }

    for (auto location : area) {
        if (!tiles.value(location.hash())->isConstructible()) {
            return false;
        }
    }

    return true;
}



bool Map::isLocationTraversable(const TileCoordinates& location) const
{
    if (!tiles.contains(location.hash())) {
        return false;
    }

    return tiles.value(location.hash())->isTraversable();
}



bool Map::hasRoadAtLocation(const TileCoordinates& location) const
{
    if (!tiles.contains(location.hash())) {
        return false;
    }

    return tiles.value(location.hash())->isRoad();
}



bool Map::canConstructRoadAtLocation(const TileCoordinates& location) const
{
    if (!tiles.contains(location.hash())) {
        return false;
    }

    auto tile(tiles.value(location.hash()));

    return tile->isConstructible() || tile->isRoad();
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



TileCoordinates Map::getBestBuildingEntryPoint(const TileArea& area) const
{
    // Fetch a location around the area, starting at the coordinates at north of left point, and turning clockwise
    // around the area.

    auto left(area.leftCorner());
    auto right(area.resolveRightCorner());
    int moveX(1);
    int moveY(0);

    TileCoordinates coordinates(left.x() - 1, left.y());// North of left corner coordinates.
    while (!tiles.value(coordinates.hash())->isRoad()) {
        coordinates = { coordinates.x() + moveX, coordinates.y() + moveY };

        if (moveX == 1 && coordinates.x() > right.x()) {
            // Overstep top corner.
            moveX = 0;
            moveY = 1;
            coordinates = { coordinates.x(), coordinates.y() + moveY };
        }
        else if (moveY == 1 && coordinates.y() > right.y()) {
            // Overstep right corner.
            moveX = -1;
            moveY = 0;
            coordinates = { coordinates.x() + moveX, coordinates.y() };
        }
        else if (moveX == -1 && coordinates.x() < left.x()) {
            // Overstep bottom corner.
            moveX = 0;
            moveY = -1;
            coordinates = { coordinates.x(), coordinates.y() + moveY };
        }
        else if (moveY == -1 && coordinates.y() < left.y()) {
            // Overstep left corner. No road nodefound.
            return TileCoordinates();
        }
    }

    return coordinates;
}
