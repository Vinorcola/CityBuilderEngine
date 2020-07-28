#include "TargetedWalkerGenerator.hpp"

#include "src/engine/map/searchEngine/SearchEngine.hpp"



TargetedWalkerGenerator::TargetedWalkerGenerator(
    ProcessableBuilding* issuer,
    const SearchEngine* searchEngine,
    const BuildingSearchCriteria* targetSearchCriteria,
    const CharacterInformation* walkerConf,
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
        auto target(dynamic_cast<ProcessableBuilding*>(results.first()));
        emit requestDynamicElementCreation(
            walkerConf,
            issuer,
            [this, target](Character* element) {
                element->assignTarget(target);
                walkers.append(element);
            }
        );
    }
}