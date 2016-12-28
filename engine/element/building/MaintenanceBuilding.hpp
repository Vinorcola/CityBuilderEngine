#ifndef MAINTENANCEBUILDING_HPP
#define MAINTENANCEBUILDING_HPP

#include "engine/element/building/AbstractProcessableBuilding.hpp"

class Map;




class MaintenanceBuilding : public AbstractProcessableBuilding
{
    private:
        Map& map;
        CycleDate nextWalkerGenerationDate;
        int numberOfWalkerOut;



    public:
        MaintenanceBuilding(Map& map, const MapArea& area, const MapCoordinates& entryPoint);

        virtual void init(const CycleDate& date);
        virtual void process(const CycleDate& date);
};

#endif // MAINTENANCEBUILDING_HPP
