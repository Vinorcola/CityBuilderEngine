#include "Map.hpp"

#include "src/engine/map/MapArea.hpp"
#include "src/engine/map/MapCoordinates.hpp"
#include "src/engine/state/MapState.hpp"



Map::Map(const QSize& size) :
    size(size)
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
