#include "Tile.hpp"

#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/NatureElementInformation.hpp"



Tile::Tile(int x, int y) :
    _coordinates(x, y),
    status(),
    _relatives(),
    pathFinding(_coordinates)
{

}



const TileCoordinates& Tile::coordinates() const
{
    return _coordinates;
}



bool Tile::isConstructible() const
{
    return status.isConstructible;
}



bool Tile::isTraversable() const
{
    return status.isTraversable;
}



bool Tile::isRoad() const
{
    return status.isRoad;
}



void Tile::registerBuildingConstruction(const BuildingInformation& conf)
{
    status.isConstructible = false;
    switch (conf.getType()) {
        case BuildingInformation::Type::MapEntryPoint:
        case BuildingInformation::Type::Road:
            status.isTraversable = true;
            status.isRoad = true;
            break;

        default:
            status.isTraversable = false;
            status.isRoad = false;
    }
}



void Tile::registerNatureElement(const NatureElementInformation& conf)
{
    status.isConstructible = false;
    status.isTraversable = conf.isTraversable();
    status.isRoad = false;
}



const Tile::Relatives& Tile::relatives() const
{
    return _relatives;
}



void Tile::pickRelatives(const QHash<QString, Tile*>& tiles)
{
    auto north(TileCoordinates::resolveHash(_coordinates.x(), _coordinates.y() - 1));
    if (tiles.contains(north)) {
        _relatives.straightNeighbours.append(tiles.value(north));
    }
    auto east(TileCoordinates::resolveHash(_coordinates.x() + 1, _coordinates.y()));
    if (tiles.contains(east)) {
        _relatives.straightNeighbours.append(tiles.value(east));
    }
    auto south(TileCoordinates::resolveHash(_coordinates.x(), _coordinates.y() + 1));
    if (tiles.contains(south)) {
        _relatives.straightNeighbours.append(tiles.value(south));
    }
    auto west(TileCoordinates::resolveHash(_coordinates.x() - 1, _coordinates.y()));
    if (tiles.contains(west)) {
        _relatives.straightNeighbours.append(tiles.value(west));
    }
    auto top(TileCoordinates::resolveHash(_coordinates.x() + 1, _coordinates.y() - 1));
    if (tiles.contains(top)) {
        _relatives.diagonalNeighbours.append(tiles.value(top));
    }
    auto right(TileCoordinates::resolveHash(_coordinates.x() + 1, _coordinates.y() + 1));
    if (tiles.contains(right)) {
        _relatives.diagonalNeighbours.append(tiles.value(right));
    }
    auto bottom(TileCoordinates::resolveHash(_coordinates.x() - 1, _coordinates.y() + 1));
    if (tiles.contains(bottom)) {
        _relatives.diagonalNeighbours.append(tiles.value(bottom));
    }
    auto left(TileCoordinates::resolveHash(_coordinates.x() - 1, _coordinates.y() - 1));
    if (tiles.contains(left)) {
        _relatives.diagonalNeighbours.append(tiles.value(left));
    }
}



Tile::PathFinding& Tile::pathFindingData() const
{
    return pathFinding;
}



qreal Tile::bestTheoreticalCost() const
{
    return pathFinding.costFromOrigin + pathFinding.theoreticalBestDistanceToDestination;
}



Tile::Status::Status() :
    isTraversable(true),
    isConstructible(true),
    isRoad(false)
{

}



Tile::PathFinding::PathFinding(const TileCoordinates& coordinates) :
    coordinates(coordinates),
    costFromOrigin(0),
    theoreticalBestDistanceToDestination(0)
{

}



void Tile::PathFinding::reset(qreal initialCost)
{
    costFromOrigin = initialCost;
}



void Tile::PathFinding::resetWithDestination(bool allowDiagonals, const Tile::PathFinding& destination, qreal initialCost)
{
    costFromOrigin = initialCost;
    theoreticalBestDistanceToDestination = allowDiagonals ?
        coordinates.chebyshevDistanceTo(destination.coordinates) :
        coordinates.manhattanDistanceTo(destination.coordinates);
}



bool Tile::PathFinding::isDestination() const
{
    return theoreticalBestDistanceToDestination == 0;
}
