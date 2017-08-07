#include "TargetedWalkerPool.hpp"

#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"



TargetedWalkerPool::TargetedWalkerPool(
    QObject* parent,
    const SearchEngine* searchEngine,
    const DynamicElementInformation* elementConf,
    const int generationInterval,
    const StaticSearchCriteria& targetSearchCriteria,
    const int max
) : WalkerPool(parent, elementConf, generationInterval, max),
    searchEngine(searchEngine),
    targetSearchCriteria(targetSearchCriteria)
{

}



void TargetedWalkerPool::process(const CycleDate& date)
{
    if (date == nextGenerationDate) {
        // Fetch a target building.
        auto results(searchEngine->search(targetSearchCriteria));
        if (results.isEmpty()) {
            // Postpone generation.
            setupNextWalkerGenerationDate(date);
        } else {
            processTargetedWalkerGeneration(date, dynamic_cast<AbstractProcessableStaticMapElement*>(results.first()));
        }
    }
}



void TargetedWalkerPool::processTargetedWalkerGeneration(const CycleDate& currentDate, AbstractProcessableStaticMapElement* target)
{
    emit requestDynamicElementCreation(
        elementConf,
        [this, currentDate, target](AbstractDynamicMapElement* element) {
            auto walker(dynamic_cast<TargetedWalker*>(element));
            if (walker) {
                walker->assignTarget(target);
                walkers.append(walker);
                setupNextWalkerGenerationDate(currentDate);
            }
        }
    );
}
