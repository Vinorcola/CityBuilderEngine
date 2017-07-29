#include "InvalidMapElementException.hpp"



InvalidMapElementException::InvalidMapElementException(const MapCoordinates& coordinates) :
    EngineException("Invalid coordinates " + coordinates.toString())
{

}



InvalidMapElementException::InvalidMapElementException(const MapArea& area) :
    EngineException("Invalid area " + area.toString())
{

}
