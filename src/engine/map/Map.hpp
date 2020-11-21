#ifndef MAP_HPP
#define MAP_HPP

#include <QtCore/QSize>

#include "src/engine/state/MapState.hpp"

class MapArea;
class MapCoordinates;

/**
 * @brief The city map.
 */
class Map
{
    private:
        const MapState state;

    public:
        explicit Map(const QSize& size);

        const MapState& getState() const;

        // Map details
        bool isLocationValid(const MapCoordinates& coordinates) const;
        bool isAreaValid(const MapArea& area) const;
};

#endif // MAP_HPP
