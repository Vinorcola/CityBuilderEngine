#include "MaintenanceBuilding.hpp"

#include <QDebug>

#include "engine/characters/RandomlyWalker.hpp"





MaintenanceBuilding::MaintenanceBuilding(Map* map, const MapCoordinates& leftCoordinates) :
    AbstractBuilding(map, MapArea(leftCoordinates, MapSize(2)), 5, 2),
    timeCycleBetweenWalkerProductions(5),
    timeCycleNeededBeforeProduction(-1)
{
    
}





void MaintenanceBuilding::process()
{
    if (timeCycleNeededBeforeProduction == 0)
    {
        // Time to generate a walker.
        generateWalker();
        --timeCycleNeededBeforeProduction; // Set to -1
    }
    else if (timeCycleNeededBeforeProduction > 0)
    {
        // Can't generate a walker yet.
        --timeCycleNeededBeforeProduction;
    }
    else
    {
        // No walker are in generation process, let's check if we can generate one.
        if (getCurrentNumberOfWalkers() < getMaxNumberOfWalkers())
        {
            timeCycleNeededBeforeProduction = timeCycleBetweenWalkerProductions;
        }
    }
}





void MaintenanceBuilding::generateWalker()
{
    qDebug() << "  - Generate a walker.";
    registerWalker(new RandomlyWalker(map, 10));
}
