#ifndef MAINTENANCEOFFICE_HPP
#define MAINTENANCEOFFICE_HPP

#include "engine/buildings/AbstractBuilding.hpp"





/**
 * @brief The base class for maintenance buildings.
 * 
 * Maintenance buildings are buildings that generate walkers that goes randomly on the roads.
 */
class MaintenanceBuilding : public AbstractBuilding
{
        Q_OBJECT
        
    public:
        MaintenanceBuilding(const MapCoordinates& leftCoordinates);
};

#endif // MAINTENANCEOFFICE_HPP
