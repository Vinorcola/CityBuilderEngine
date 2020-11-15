#ifndef ABSTRACTPROCESSABLEBUILDING_HPP
#define ABSTRACTPROCESSABLEBUILDING_HPP

#include "src/engine/element/static/building/AbstractBuilding.hpp"
#include "src/engine/map/MapCoordinates.hpp"
#include "src/engine/processing/AbstractProcessable.hpp"

class BuildingInformation;
class Character;
class MapAreea;

class AbstractProcessableBuilding : public AbstractBuilding, public AbstractProcessable
{
    private:
        MapCoordinates entryPoint;

    public:
        AbstractProcessableBuilding(
            const BuildingInformation& conf,
            const MapArea& area,
            const MapCoordinates& entryPoint
        );

        const MapCoordinates& getEntryPoint() const;

        virtual bool processInteraction(const CycleDate& date, Character& actor);
};

#endif // ABSTRACTPROCESSABLEBUILDING_HPP
