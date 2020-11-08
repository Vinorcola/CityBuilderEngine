#ifndef MAPAREA_HPP
#define MAPAREA_HPP

#include <QtCore/QString>

#include "src/engine/map/MapCoordinates.hpp"
#include "src/engine/map/MapSize.hpp"

/**
 * @brief Represent an area on the map.
 *
 * An area is created with some coordinates and a size. If no size provided, then an area of size 1 is created.
 */
class MapArea
{
    public:
        class ConstIterator
        {
            private:
                const int xMin;
                const int xMax;
                const int yMin;
                const int yMax;
                int x;
                int y;

            public:
                ConstIterator(const MapCoordinates& left, const MapCoordinates& right);
                const ConstIterator& operator ++();
                MapCoordinates operator *() const;
                bool operator !=(const ConstIterator& other) const;
                const ConstIterator& toEnd();
        };

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

        void moveTo(const MapCoordinates& left);

        // Coordinates iterator
        ConstIterator begin() const;
        ConstIterator end() const;

        // DEBUG //
        QString toString() const;
};

#endif // MAPAREA_HPP
