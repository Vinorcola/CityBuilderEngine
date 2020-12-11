#ifndef MAPSIZE_HPP
#define MAPSIZE_HPP

#include <QtCore/QSize>

/**
 * @brief Represent a size (typically for an area or a static element) on the map.
 *
 * The size is counted in number of tiles.
 */
class MapSize
{
    private:
        QSize size;

    public:
        explicit MapSize(int size = 1);
        MapSize(int width, int height);

        bool isSquare() const;
        int getWidth() const;
        int getHeight() const;

        // DEBUG //
        QString toString() const;
};

#endif // MAPSIZE_HPP
