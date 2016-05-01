#include "MaintenanceBuilding.hpp"

#include <QDebug>





MaintenanceBuilding::MaintenanceBuilding(const MapCoordinates& leftCoordinates) :
    AbstractBuilding(MapArea(leftCoordinates, MapSize(2)), 5),
    maxWalkers(1),
    timeCycleBetweenProduction(5),
    currentNumberOfWalker(0),
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
        if (currentNumberOfWalker < maxWalkers)
        {
            timeCycleNeededBeforeProduction = timeCycleBetweenProduction;
        }
    }
}





void MaintenanceBuilding::generateWalker()
{
    qDebug() << "Generate a walker.";
    ++currentNumberOfWalker;
}
