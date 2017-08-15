#include "MapSize.hpp"



MapSize::MapSize() :
    MapSize(1)
{

}


MapSize::MapSize(const int value) :
    value(value)
{

}



bool MapSize::operator !=(const MapSize& other) const
{
    return value != other.value;
}



int MapSize::getValue() const
{
    return value;
}
