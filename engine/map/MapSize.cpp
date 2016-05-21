#include "MapSize.hpp"





MapSize::MapSize() :
    MapSize(1)
{

}




MapSize::MapSize(const int value) :
    value(value)
{

}





int MapSize::getValue() const
{
    return value;
}
