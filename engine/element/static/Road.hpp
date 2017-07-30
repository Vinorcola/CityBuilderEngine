#ifndef ROAD_HPP
#define ROAD_HPP

#include "engine/element/static/AbstractStaticMapElement.hpp"

/**
 * @brief A road building.
 */
class Road : public AbstractStaticMapElement
{
    public:
        Road(const MapCoordinates& coordinates);
};

#endif // ROAD_HPP
