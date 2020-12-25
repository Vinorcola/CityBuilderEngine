#include "Map.hpp"

#include <QtCore/QDebug>

#include "src/engine/loader/CityLoader.hpp"
#include "src/engine/map/Tile.hpp"
#include "src/engine/processing/CycleDate.hpp"
#include "src/exceptions/NotImplementedException.hpp"
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
    tiles(generateTiles(size)),
    civilianEntryPoint(CivilianEntryPoint::Create(
        dynamicElements,
        conf.getBuildingConf("mapEntryPoint"),
        { loader.getMapEntryPoint(), 1 },
        Direction::West,
        *tiles.value(loader.getMapEntryPoint().hash()),
        conf.getCharacterConf("immigrant")
    )),
    pathGenerator(),
    staticElements(dynamicElements, populationRegistry, workingPlaceRegistry, pathGenerator, *civilianEntryPoint.get()),
    dynamicElements(pathGenerator, staticElements.getBuildingSearchEngine(), staticElements.getNatureElementSearchEngine())
{

}



Map::~Map()
{
    qDeleteAll(tiles);
}



QList<TileCoordinates> Map::getShortestPathForRoad(const TileCoordinates& origin, const TileCoordinates& target) const
{
    if (!isLocationValid(target)) {
        return {};
    }

    auto pathTiles(pathGenerator.generateShortestPathForRoad(
        *tiles.value(origin.hash()),
        *tiles.value(target.hash())
    ));

    QList<TileCoordinates> path;
    for (auto tile : pathTiles) {
        path.append(tile->coordinates());
    }

    return path;
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
        try {
            staticElements.generateProcessableBuilding(conf, area, orientation, getBestBuildingEntryPoint(area));
        }
        catch (NotImplementedException) {
            qDebug() << "WARNING: For now, buildings must be linked to a road at their construction. Skipping the creation.";
        }
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



void Map::process(const CycleDate& date)
{
    // Note: order is important: dynamic elements, entry points & static elements.
    dynamicElements.process(date);
    civilianEntryPoint->process(date);
    if (date.isBuildingCycle()) {
        staticElements.process(date);
    }
}



Tile& Map::getBestBuildingEntryPoint(const TileArea& area) const
{
    // Fetch a location around the area, starting at the coordinates at north of left point, and turning clockwise
    // around the area.

    auto& left(area.leftCorner());
    auto right(area.resolveRightCorner());
    // Init with coordinates of northern tile from left corner.
    int x(left.x());
    int y(left.y() - 1);
    int moveX(1);
    int moveY(0);
    auto tile(tiles.value(TileCoordinates::resolveHash(x, y)));

    while (!tile || !tile->isRoad()) {
        x += moveX;
        y += moveY;

        if (moveX == 1 && x > right.x()) {
            // Overstep top corner.
            moveX = 0;
            moveY = 1;
            ++y;
        }
        else if (moveY == 1 && y > right.y()) {
            // Overstep right corner.
            moveX = -1;
            moveY = 0;
            --x;
        }
        else if (moveX == -1 && x < left.x()) {
            // Overstep bottom corner.
            moveX = 0;
            moveY = -1;
            --y;
        }
        else if (moveY == -1 && y < left.y()) {
            // Overstep left corner. No road nodefound.
            throw NotImplementedException("Building need to have a valid entry point.");
        }

        tile = tiles.value(TileCoordinates::resolveHash(x, y));
    }

    return *tile;
}



QHash<QString, owner<Tile*> > Map::generateTiles(const QSize& size)
{
    QHash<QString, owner<Tile*>> tiles;
    int line(0);
    int column(0);
    while (line < size.height()) {
        // NOTE: Because we divide by 2 and casting as integer, we deliberately remove floating precision. However, the
        // adjustment needs to be 1 higher when "mapSize.width() - line" become negative. This is because -0.5 is cast
        // to 0 insted of -1.
        int adjust(line > size.width() ? 1 : 2);
        while (column < (size.width() - line + adjust) / 2) {
            auto tile(new Tile(column, line + column));
            tiles.insert(TileCoordinates::resolveHash(column, line + column), tile);

            ++column;
        }
        ++line;
        column = -line / 2;
    }
    for (auto tile : tiles) {
        tile->pickRelatives(tiles);
    }

    return tiles;
}
