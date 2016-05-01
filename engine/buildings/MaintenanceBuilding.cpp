#include "MaintenanceBuilding.hpp"

#include <QDebug>

#include "engine/characters/RandomlyWalker.hpp"





MaintenanceBuilding::MaintenanceBuilding(const MapCoordinates& leftCoordinates) :
    AbstractBuilding(MapArea(leftCoordinates, MapSize(2)), 5, 2),
    timeCycleBetweenWalkerProductions(5),
    currentNumberOfWalker(getCurrentNumberOfWalkers()),
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
        if (currentNumberOfWalker < getMaxNumberOfWalkers())
        {
            timeCycleNeededBeforeProduction = timeCycleBetweenWalkerProductions;
        }
    }
}





void MaintenanceBuilding::generateWalker()
{
    qDebug() << "Generate a walker.";
    currentNumberOfWalker = registerWalker(new RandomlyWalker);
}
