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
        
    private:
        const int timeCycleBetweenWalkerProductions;
        
        int currentNumberOfWalker;
        int timeCycleNeededBeforeProduction;
        
        
        
    public:
        MaintenanceBuilding(const MapCoordinates& leftCoordinates);
        
        
        
        virtual void process();
        
        
        
    protected:
        void generateWalker();
};

#endif // MAINTENANCEOFFICE_HPP
