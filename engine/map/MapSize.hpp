#ifndef MAPSIZE_HPP
#define MAPSIZE_HPP

/**
 * @brief Represent a size (typically for an area or a static element) on the map.
 *
 * The size is counted in number of tiles.
 */
class MapSize
{
    private:
        int value;

    public:
        MapSize();

        explicit MapSize(const int value);

        int getValue() const;
};

#endif // MAPSIZE_HPP
