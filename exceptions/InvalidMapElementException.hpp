#ifndef INVALIDMAPELEMENTEXCEPTION_HPP
#define INVALIDMAPELEMENTEXCEPTION_HPP

#include "exceptions/EngineException.hpp"
#include "global/MapElement.hpp"





class InvalidMapElementException : public EngineException
{
    public:
        InvalidMapElementException(const MapCoordinates& coordinates);
        InvalidMapElementException(const MapArea& area);
};

#endif // INVALIDMAPELEMENTEXCEPTION_HPP
