#ifndef MAPDETAILSINTERFACE_HPP
#define MAPDETAILSINTERFACE_HPP

class MapCoordinates;

class MapDetailsInterface
{
    public:
        virtual ~MapDetailsInterface() {};

        /**
         * @brief Indicate if the given location is traversable.
         */
        virtual bool isLocationTraversable(const MapCoordinates& location) const = 0;

        /**
         * @brief Indicate if there is a road on the given location.
         */
        virtual bool hasRoadAtLocation(const MapCoordinates& location) const = 0;

        /**
         * @brief Indicate if the given location can be constructed with a road.
         *
         * Note that if a road already exists at the given location, this function will return true.
         */
        virtual bool canConstructRoadAtLocation(const MapCoordinates& location) const = 0;
};

#endif // MAPDETAILSINTERFACE_HPP
