#include "Tile.hpp"

#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/NatureElementInformation.hpp"



Tile::Status::Status() :
    isTraversable(true),
    isConstructible(true),
    isRoad(false)
{

}



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



QString Tile::hashCoordinates(int x, int y)
{
    return QString::number(x) + ';' + QString::number(y);
}



QString Tile::hashCoordinates(QPoint coordinates)
{
    return hashCoordinates(coordinates.x(), coordinates.y());
}
