#include "InvalidMapElementException.hpp"





InvalidMapElementException::InvalidMapElementException(const MapCoordinates& coordinates) :
    EngineException("Invalid coordinates (" + QString::number(coordinates.getX()) + ";" + QString::number(coordinates.getY()) + ")")
{
    
}





InvalidMapElementException::InvalidMapElementException(const MapArea& area) :
    EngineException("Invalid area (" + QString::number(area.getLeft().getX()) + ";" + QString::number(area.getLeft().getY()) + ") of size " + QString::number(area.getSize().getSize()))
{
    
}
