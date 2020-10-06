#ifndef HOUSEBUILDING_HPP
#define HOUSEBUILDING_HPP

#include "src/engine/element/static/ProcessableBuilding.hpp"

class MapEntryPoint;

class HouseBuilding : public ProcessableBuilding
{
        Q_OBJECT

    private:
        MapEntryPoint& immigrantGenerator;
        int population;

    public:
        HouseBuilding(
            QObject* parent,
            const BuildingInformation& conf,
            const MapArea& area,
            const MapCoordinates& entryPoint,
            MapEntryPoint& immigrantGenerator
        );

        virtual void init(const CycleDate& date);

        virtual void process(const CycleDate& date);

        virtual bool processInteraction(const CycleDate& date, Character& actor);
};

#endif // HOUSEBUILDING_HPP
