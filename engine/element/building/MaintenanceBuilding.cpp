#include "MaintenanceBuilding.hpp"

#include <QDebug>

#include "engine/map/Map.hpp"



const int WALKER_GENERATION_DATE_GAP(5);
const int MAX_NUMBER_OF_WALKER(1);





MaintenanceBuilding::MaintenanceBuilding(Map& map, const MapArea& area, const MapCoordinates& entryPoint) :
    AbstractProcessableBuilding(area, entryPoint),
    map(map),
    nextWalkerGenerationDate(),
    numberOfWalkerOut(0)
{
    nextWalkerGenerationDate.add(WALKER_GENERATION_DATE_GAP);

    qDebug() << "Created maintenance building at" << area.toString();
}





void MaintenanceBuilding::process(const CycleDate& date)
{
    if (numberOfWalkerOut < MAX_NUMBER_OF_WALKER)
    {
        if (date == nextWalkerGenerationDate)
        {
            map.createDynamicElement(Map::DynamicElementType::RandomWalker, getEntryPoint());
        }
    }
}
