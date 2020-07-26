#ifndef INVALIDMAPELEMENTEXCEPTION_HPP
#define INVALIDMAPELEMENTEXCEPTION_HPP

#include "src/exceptions/EngineException.hpp"

class MapArea;
class MapCoordinates;

class InvalidMapElementException : public EngineException
{
    public:
        InvalidMapElementException(const MapCoordinates& coordinates);
        InvalidMapElementException(const MapArea& area);
};

#endif // INVALIDMAPELEMENTEXCEPTION_HPP
