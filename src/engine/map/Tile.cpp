#include "Tile.hpp"

#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/NatureElementInformation.hpp"



Tile::Tile(int x, int y) :
    coordinates(x, y),
    hash(hashCoordinates(x, y)),
    status()
{

}



const QString& Tile::getHash() const
{
    return hash;
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



void Tile::pickRelatives(const QHash<QString, Tile*>& tiles)
{
    auto north(hashCoordinates(coordinates.x(), coordinates.y() - 1));
    if (tiles.contains(north)) {
        relatives.north = tiles.value(north);
    }
    auto south(hashCoordinates(coordinates.x(), coordinates.y() + 1));
    if (tiles.contains(south)) {
        relatives.south = tiles.value(south);
    }
    auto east(hashCoordinates(coordinates.x() + 1, coordinates.y()));
    if (tiles.contains(east)) {
        relatives.east = tiles.value(east);
    }
    auto west(hashCoordinates(coordinates.x() - 1, coordinates.y()));
    if (tiles.contains(west)) {
        relatives.west = tiles.value(west);
    }
    auto top(hashCoordinates(coordinates.x() + 1, coordinates.y() - 1));
    if (tiles.contains(top)) {
        relatives.top = tiles.value(top);
    }
    auto bottom(hashCoordinates(coordinates.x() - 1, coordinates.y() + 1));
    if (tiles.contains(bottom)) {
        relatives.bottom = tiles.value(bottom);
    }
    auto left(hashCoordinates(coordinates.x() - 1, coordinates.y() - 1));
    if (tiles.contains(left)) {
        relatives.left = tiles.value(left);
    }
    auto right(hashCoordinates(coordinates.x() + 1, coordinates.y() + 1));
    if (tiles.contains(right)) {
        relatives.right = tiles.value(right);
    }
}



QString Tile::hashCoordinates(int x, int y)
{
    return QString::number(x) + ';' + QString::number(y);
}



QString Tile::hashCoordinates(QPoint coordinates)
{
    return hashCoordinates(coordinates.x(), coordinates.y());
}



Tile::Status::Status() :
    isTraversable(true),
    isConstructible(true),
    isRoad(false)
{

}



Tile::Relatives::Relatives() :
    north(nullptr),
    south(nullptr),
    east(nullptr),
    west(nullptr),
    top(nullptr),
    bottom(nullptr),
    left(nullptr),
    right(nullptr)
{

}
