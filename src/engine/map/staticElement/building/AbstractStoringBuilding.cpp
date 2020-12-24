#include "AbstractStoringBuilding.hpp"



AbstractStoringBuilding::AbstractStoringBuilding(
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const Tile& entryPointTile
) :
    AbstractProcessableBuilding(conf, area, orientation, entryPointTile)
{

}
