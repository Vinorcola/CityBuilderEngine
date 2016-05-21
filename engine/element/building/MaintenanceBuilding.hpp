#ifndef MAINTENANCEBUILDING_HPP
#define MAINTENANCEBUILDING_HPP

#include "engine/element/building/AbstractProcessableBuilding.hpp"




class MaintenanceBuilding : public AbstractProcessableBuilding
{
    public:
        MaintenanceBuilding(Map& map, const MapArea& area);



        virtual void process();
};

#endif // MAINTENANCEBUILDING_HPP
