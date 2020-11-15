#ifndef MAP_HPP
#define MAP_HPP

#include <QtCore/QSize>

class MapArea;
class MapCoordinates;

/**
 * @brief The city map.
 */
class Map
{
    private:
        const QSize size;

    public:
        explicit Map(const QSize& size);

        // Size
        const QSize& getSize() const;

        // Map details
        bool isLocationValid(const MapCoordinates& coordinates) const;
        bool isAreaValid(const MapArea& area) const;
};

#endif // MAP_HPP
