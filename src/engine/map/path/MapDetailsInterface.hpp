#ifndef MAPDETAILSINTERFACE_HPP
#define MAPDETAILSINTERFACE_HPP

class TileCoordinates;

class MapDetailsInterface
{
    public:
        virtual ~MapDetailsInterface() {};

        /**
         * @brief Indicate if the given location is traversable.
         */
        virtual bool isLocationTraversable(const TileCoordinates& location) const = 0;

        /**
         * @brief Indicate if there is a road on the given location.
         */
        virtual bool hasRoadAtLocation(const TileCoordinates& location) const = 0;

        /**
         * @brief Indicate if the given location can be constructed with a road.
         *
         * Note that if a road already exists at the given location, this function will return true.
         */
        virtual bool canConstructRoadAtLocation(const TileCoordinates& location) const = 0;
};

#endif // MAPDETAILSINTERFACE_HPP
