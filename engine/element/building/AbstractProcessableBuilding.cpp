#include "AbstractProcessableBuilding.hpp"





AbstractProcessableBuilding::AbstractProcessableBuilding(Map& map, const MapArea& area) :
    AbstractBuilding(map, area),
    AbstractProcessable(map.getProcessor())
{

}
