#ifndef MAP_HPP
#define MAP_HPP

#include <QtCore/QSize>

#include "src/engine/map/dynamicElement/DynamicElementRegistry.hpp"

class MapArea;
class MapCoordinates;
class MapState;

/**
 * @brief The city map.
 */
class Map
{
    public:
        explicit Map(const QSize& size);

        MapState getState() const;

        // Map details
        bool isLocationValid(const MapCoordinates& coordinates) const;
        bool isAreaValid(const MapArea& area) const;

    private:
        const QSize size;
};

#endif // MAP_HPP
