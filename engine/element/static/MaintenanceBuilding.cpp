#include "MaintenanceBuilding.hpp"

#include <QDebug>

#include "defines.hpp"
#include "engine/map/Map.hpp"

const int WALKER_GENERATION_DATE_GAP(4 * CYCLE_PER_SECOND);
const int MAX_NUMBER_OF_WALKER(2);



MaintenanceBuilding::MaintenanceBuilding(QObject* parent, const MapArea& area, const MapCoordinates& entryPoint) :
    AbstractProcessableStaticMapElement(parent, area, entryPoint),
    nextWalkerGenerationDate(),
    walkers()
{
    qDebug() << "  - Created maintenance building at" << area.toString();
}



void MaintenanceBuilding::init(const CycleDate& date)
{
    setupNextWalkerGenerationDate(date);
}



void MaintenanceBuilding::process(const CycleDate& date)
{
    if (date == nextWalkerGenerationDate) {
        emit requestDynamicElementCreation(
            AbstractDynamicMapElement::Type::Maintenance,
            30,
#ifdef SLOW_MOTION
            0.25 / CYCLE_PER_SECOND,
#else
            2.0 / CYCLE_PER_SECOND,
#endif
            [this, date](AbstractDynamicMapElement* element) {
                auto walker(dynamic_cast<RandomWalker*>(element));
                if (walker) {
                    walkers.append(walker);
                    setupNextWalkerGenerationDate(date);
                }
            }
        );
    }
}



void MaintenanceBuilding::processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor)
{
    for (auto walker : walkers) {
        if (walker == actor) {
            emit requestDynamicElementDestruction(actor, [this, walker, date]() {
                walkers.removeOne(walker);
                setupNextWalkerGenerationDate(date);
            });
            return;
        }
    }
}



void MaintenanceBuilding::setupNextWalkerGenerationDate(const CycleDate& currentDate)
{
    if (getEntryPoint().isValid() && walkers.size() < MAX_NUMBER_OF_WALKER && nextWalkerGenerationDate <= currentDate) {
        nextWalkerGenerationDate = currentDate;
        nextWalkerGenerationDate.add(WALKER_GENERATION_DATE_GAP);
    }
}
