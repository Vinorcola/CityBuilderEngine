#ifndef TILEAREA_HPP
#define TILEAREA_HPP

#include "src/global/geometry/TileAreaSize.hpp"
#include "src/global/geometry/TileCoordinates.hpp"

/**
 * @brief A tile area on the map.
 */
class TileArea
{
    public:
        class Iterator
        {
            public:
                Iterator(const TileCoordinates& left, const TileCoordinates& right);
                static Iterator CreateEnd(const TileCoordinates& left, const TileCoordinates& right);
                const Iterator& operator ++();
                TileCoordinates operator *() const;
                bool operator !=(const Iterator& other) const;

            private:
                const TileCoordinates LEFT;
                const TileCoordinates RIGHT;
                int x;
                int y;
        };

    public:
        TileArea(const TileCoordinates& leftCorner, const TileAreaSize& size);

        const TileAreaSize& size() const;
        const TileCoordinates& leftCorner() const;
        TileCoordinates resolveTopCorner() const;
        TileCoordinates resolveRightCorner() const;
        TileCoordinates resolveBottomCorner() const;

        void moveTo(const TileCoordinates& leftCorner);

        // Covered tiles.
        Iterator begin() const;
        Iterator beginAfterLeftCorner() const;
        Iterator end() const;

        QString toString() const;

    private:
        TileCoordinates _leftCorner;
        TileAreaSize _size;
};

#endif // TILEAREA_HPP
