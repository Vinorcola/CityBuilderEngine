#include "MaintenanceBuilding.hpp"

#include <QDebug>

#include "defines.hpp"
#include "engine/map/Map.hpp"

const int WALKER_GENERATION_DATE_GAP(4 * CYCLE_PER_SECOND);
const int MAX_NUMBER_OF_WALKER(2);



MaintenanceBuilding::MaintenanceBuilding(Map& map, const MapArea& area, const MapCoordinates& entryPoint) :
    AbstractProcessableStaticMapElement(area, entryPoint),
    map(map),
    nextWalkerGenerationDate(),
    walkers()
{
    qDebug() << "  - Created maintenance building at" << area.toString();
}



void MaintenanceBuilding::init(const CycleDate& date)
{
    setupWalkerGeneration(date);
}



void MaintenanceBuilding::process(const CycleDate& date)
{
    if (date == nextWalkerGenerationDate) {
        walkers.append(
            qWeakPointerCast<RandomWalker, AbstractDynamicMapElement>(map.createDynamicElement(
                Map::DynamicElementType::RandomWalker,
                this,
                30,
#ifdef SLOW_MOTION
                0.25 / CYCLE_PER_SECOND
#else
                2.0 / CYCLE_PER_SECOND
#endif
            ))
        );
        setupWalkerGeneration(date);
    }
}



void MaintenanceBuilding::processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor)
{
    auto iterator(walkers.begin());
    while (iterator != walkers.end()) {
        auto walker(iterator->toStrongRef());
        if (walker) {
            if (walker == actor) {
                map.destroyDynamicElement(actor);
                iterator = walkers.erase(iterator);
                setupWalkerGeneration(date);
            } else {
                ++iterator;
            }
        } else {
            iterator = walkers.erase(iterator);
            setupWalkerGeneration(date);
        }
    }
}



void MaintenanceBuilding::setupWalkerGeneration(const CycleDate& currentDate)
{
    if (getEntryPoint().isValid() && walkers.size() < MAX_NUMBER_OF_WALKER && nextWalkerGenerationDate <= currentDate) {
        nextWalkerGenerationDate = currentDate;
        nextWalkerGenerationDate.add(WALKER_GENERATION_DATE_GAP);
    }
}
