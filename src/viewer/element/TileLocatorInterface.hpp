#ifndef TILEACCESSORINTERFACE_HPP
#define TILEACCESSORINTERFACE_HPP

class MapCoordinates;
class TileView;

class TileLocatorInterface
{
    public:
        /**
         * @brief Return the tile at the given location.
         */
        virtual TileView& getTileAt(const MapCoordinates& location) const = 0;
};

#endif // TILEACCESSORINTERFACE_HPP
