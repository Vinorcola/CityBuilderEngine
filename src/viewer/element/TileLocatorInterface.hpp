#ifndef TILEACCESSORINTERFACE_HPP
#define TILEACCESSORINTERFACE_HPP

class TileCoordinates;
class TileView;

class TileLocatorInterface
{
    public:
        /**
         * @brief Return the tile at the given location.
         */
        virtual TileView& getTileAt(const TileCoordinates& location) const = 0;
};

#endif // TILEACCESSORINTERFACE_HPP
