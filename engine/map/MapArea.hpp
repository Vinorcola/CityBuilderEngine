#ifndef MAPAREA_HPP
#define MAPAREA_HPP

#include <QtCore/QString>

#include "engine/map/MapCoordinates.hpp"
#include "engine/map/MapSize.hpp"

/**
 * @brief Represent an area on the map.
 *
 * An area is created with some coordinates and a size. If no size provided, then an area of size 1 is created.
 */
class MapArea
{
    private:
        MapSize size;
        MapCoordinates left;

    public:
        MapArea();

        explicit MapArea(const MapCoordinates& left);

        MapArea(const MapCoordinates& left, const MapSize& size);

        const MapSize getSize() const;

        const MapCoordinates& getLeft() const;

        MapCoordinates getRight() const;

        MapCoordinates getTop() const;

        MapCoordinates getBottom() const;

        bool isInside(const MapCoordinates& coordinates) const;

        // DEBUG //
        QString toString() const;
};

#endif // MAPAREA_HPP
