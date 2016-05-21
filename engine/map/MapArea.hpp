#ifndef MAPAREA_HPP
#define MAPAREA_HPP

#include "engine/map/MapCoordinates.hpp"
#include "engine/map/MapSize.hpp"





class MapArea
{
    private:
        MapSize size;
        MapCoordinates left;



    public:
        MapArea();
        explicit MapArea(const MapCoordinates& left);
        MapArea(const MapCoordinates& left, const MapSize& size);

        const MapSize getSize() const;
        const MapCoordinates& getLeft() const;
        MapCoordinates getRight() const;
        MapCoordinates getTop() const;
        MapCoordinates getBottom() const;
        bool isInside(const MapCoordinates& coordinates) const;
        QString toString() const;
};

#endif // MAPAREA_HPP
