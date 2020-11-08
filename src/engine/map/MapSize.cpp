#include "MapSize.hpp"

#include <cassert>



MapSize::MapSize() :
    MapSize(1)
{

}


MapSize::MapSize(const int value) :
    value(value)
{
    assert(value > 0);
}



bool MapSize::operator !=(const MapSize& other) const
{
    return value != other.value;
}



int MapSize::getValue() const
{
    return value;
}
