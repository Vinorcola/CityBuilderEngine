#ifndef TILEACCESSORINTERFACE_HPP
#define TILEACCESSORINTERFACE_HPP

class MapCoordinates;
class Tile;

class TileLocatorInterface
{
    public:
        /**
         * @brief Return the tile at the given location.
         */
        virtual Tile& getTileAt(const MapCoordinates& location) const = 0;
};

#endif // TILEACCESSORINTERFACE_HPP
