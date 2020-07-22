#include "TargetedWalkerGenerator.hpp"

#include "engine/map/searchEngine/SearchEngine.hpp"



TargetedWalkerGenerator::TargetedWalkerGenerator(
    AbstractProcessableStaticMapElement* issuer,
    const SearchEngine* searchEngine,
    const StaticSearchCriteria* targetSearchCriteria,
    const DynamicElementInformation* walkerConf,
    const int generationInterval,
    const int maxWalkers
) :
    AbstractWalkerGenerator(issuer, walkerConf, generationInterval, maxWalkers),
    searchEngine(searchEngine),
    targetSearchCriteria(*targetSearchCriteria)
{

}



void TargetedWalkerGenerator::generate()
{
    // Fetch a target building.
    auto results(searchEngine->search(targetSearchCriteria));

    if (!results.isEmpty()) {
        auto target(dynamic_cast<AbstractProcessableStaticMapElement*>(results.first()));
        emit requestDynamicElementCreation(
            walkerConf,
            issuer,
            [this, target](Character* element) {
                static_cast<TargetedWalker*>(element)->assignTarget(target);
                walkers.append(static_cast<TargetedWalker*>(element));
            }
        );
    }
}
