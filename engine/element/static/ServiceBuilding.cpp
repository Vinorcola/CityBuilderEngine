#include "ServiceBuilding.hpp"

#include <QDebug>

#include "defines.hpp"
#include "engine/map/Map.hpp"

const int WALKER_GENERATION_DATE_GAP(8 * CYCLE_PER_SECOND);



ServiceBuilding::ServiceBuilding(QObject* parent, const StaticElementInformation* conf, const MapArea& area, const MapCoordinates& entryPoint) :
    AbstractProcessableStaticMapElement(parent, conf, area, entryPoint),
    nextWalkerGenerationDate(),
    walkers()
{
    qDebug() << "  - Created maintenance building at" << area.toString();
}



void ServiceBuilding::init(const CycleDate& date)
{
    setupNextWalkerGenerationDate(date);
}



void ServiceBuilding::process(const CycleDate& date)
{
    if (date == nextWalkerGenerationDate) {
        emit requestDynamicElementCreation(
            conf->getWalkerConf(),
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



void ServiceBuilding::processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor)
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



void ServiceBuilding::setupNextWalkerGenerationDate(const CycleDate& currentDate)
{
    if (getEntryPoint().isValid() && walkers.size() < conf->getMaxNumberOfWalkers() && nextWalkerGenerationDate <= currentDate) {
        nextWalkerGenerationDate = currentDate;
        nextWalkerGenerationDate.add(WALKER_GENERATION_DATE_GAP);
    }
}
