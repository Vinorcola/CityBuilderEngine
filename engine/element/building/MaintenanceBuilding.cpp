#include "MaintenanceBuilding.hpp"

#include <QDebug>

#include "defines.hpp"
#include "engine/map/Map.hpp"

const int WALKER_GENERATION_DATE_GAP(10);
const int MAX_NUMBER_OF_WALKER(2);



MaintenanceBuilding::MaintenanceBuilding(Map& map, const MapArea& area, const MapCoordinates& entryPoint) :
    AbstractProcessableBuilding(area, entryPoint),
    map(map),
    nextWalkerGenerationDate(),
    walkers()
{
    qDebug() << "  - Created maintenance building at" << area.toString();
}



void MaintenanceBuilding::init(const CycleDate& date)
{
    nextWalkerGenerationDate = date;
    nextWalkerGenerationDate.add(WALKER_GENERATION_DATE_GAP);
}



void MaintenanceBuilding::process(const CycleDate& date)
{
    if (date == nextWalkerGenerationDate) {
        walkers.append(
            static_cast<RandomWalker*>(map.createDynamicElement(
                Map::DynamicElementType::RandomWalker,
                getEntryPoint(),
                15,
#ifdef SLOW_MOTION
                0.25 / CYCLE_PER_SECOND
#else
                2.0 / CYCLE_PER_SECOND
#endif
            ))
        );

        if (walkers.size() < MAX_NUMBER_OF_WALKER) {
            nextWalkerGenerationDate = date;
            nextWalkerGenerationDate.add(WALKER_GENERATION_DATE_GAP);
        }
    }

    auto iterator(walkers.begin());
    while (iterator != walkers.end()) {
        if ((*iterator)->reachedTarget()) {
            map.destroyDynamicElement(*iterator);
            iterator = walkers.erase(iterator);

            nextWalkerGenerationDate = date;
            nextWalkerGenerationDate.add(WALKER_GENERATION_DATE_GAP);
        } else {
            ++iterator;
        }
    }
}
