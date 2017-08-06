#ifndef ROAD_HPP
#define ROAD_HPP

#include "engine/element/static/AbstractStaticMapElement.hpp"

/**
 * @brief A road.
 */
class Road : public AbstractStaticMapElement
{
    public:
        Road(const StaticElementInformation* conf, const MapCoordinates& coordinates);
};

#endif // ROAD_HPP
