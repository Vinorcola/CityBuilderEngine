#ifndef MAPDETAILSINTERFACE_HPP
#define MAPDETAILSINTERFACE_HPP

class MapCoordinates;

class MapDetailsInterface
{
    public:
        virtual ~MapDetailsInterface();

        /**
         * @brief Indicate if the given location is traversable.
         */
        virtual bool isLocationTraversable(const MapCoordinates& location) const = 0;

        /**
         * @brief Indicate if there is a road on the given location.
         */
        virtual bool isLocationARoad(const MapCoordinates& location) const = 0;
};

#endif // MAPDETAILSINTERFACE_HPP
