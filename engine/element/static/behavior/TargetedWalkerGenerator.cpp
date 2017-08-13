#include "TargetedWalkerGenerator.hpp"

#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"



TargetedWalkerGenerator::TargetedWalkerGenerator(QObject* parent, const SearchEngine* searchEngine, const StaticSearchCriteria& targetSearchCriteria, const DynamicElementInformation* walkerConf, const int generationInterval, const int maxWalkers) :
    AbstractStaticElementBehavior(parent),
    searchEngine(searchEngine),
    targetSearchCriteria(targetSearchCriteria),
    walkerConf(walkerConf),
    generationInterval(generationInterval),
    maxWalkers(maxWalkers),
    generationSpeedRatio(0.0),
    needToSetupNextGenerationDate(true),
    nextGenerationDate(),
    walkers()
{

}



bool TargetedWalkerGenerator::contains(const TargetedWalker* walker) const
{
    for (auto walkerFromList : walkers) {
        if (walkerFromList == walker) {
            return true;
        }
    }

    return false;
}



void TargetedWalkerGenerator::clean()
{
    auto iterator(walkers.begin());
    while (iterator != walkers.end()) {
        if (iterator->isNull()) {
            iterator = walkers.erase(iterator);
            needToSetupNextGenerationDate = true;
        } else {
            ++iterator;
        }
    }
}



void TargetedWalkerGenerator::setGenerationSpeedRatio(qreal ratio, const CycleDate& currentDate)
{
    // If ratio does not change, we avoid useless calculations.
    if (generationSpeedRatio == ratio) {
        return;
    }

    if (ratio <= 0.0) {
        generationSpeedRatio = 0.0;
        nextGenerationDate.reset();
    } else {
        if (ratio > 1.0) {
            ratio = 1.0;
        }

        // Calculate the next generation date and setup ratio.
        if (nextGenerationDate) {
            int dateInterval(nextGenerationDate - currentDate);
            nextGenerationDate.reassign(currentDate, dateInterval * ratio / generationSpeedRatio);
            generationSpeedRatio = ratio;
        } else if (generationSpeedRatio == 0.0) {
            generationSpeedRatio = ratio;
            setupNextGenerationDate(currentDate);
        }
    }
}



void TargetedWalkerGenerator::process(const CycleDate& date)
{
    if (needToSetupNextGenerationDate) {
        setupNextGenerationDate(date);
    }
    if (date == nextGenerationDate) {
        // Fetch a target building.
        auto results(searchEngine->search(targetSearchCriteria));

        if (!results.isEmpty()) {
            generate(dynamic_cast<AbstractProcessableStaticMapElement*>(results.first()));
        }

        setupNextGenerationDate(date);
    }
}



bool TargetedWalkerGenerator::processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor)
{
    // Process a random walker issued from this walker generator.
    auto walker(dynamic_cast<TargetedWalker*>(actor));
    if (walker && contains(walker)) {
        emit requestDynamicElementDestruction(walker, [this, date]() {
            clean();
        });

        return true;
    }

    return false;
}



void TargetedWalkerGenerator::setupNextGenerationDate(const CycleDate& currentDate)
{
    if (generationSpeedRatio > 0.0 && walkers.size() < maxWalkers && nextGenerationDate <= currentDate) {
        nextGenerationDate.reassign(currentDate, generationInterval * generationSpeedRatio);
    }

    needToSetupNextGenerationDate = false;
}



void TargetedWalkerGenerator::generate(AbstractProcessableStaticMapElement* target)
{
    emit requestDynamicElementCreation(
        walkerConf,
        [this, target](AbstractDynamicMapElement* element) {
            static_cast<TargetedWalker*>(element)->assignTarget(target);
            walkers.append(static_cast<TargetedWalker*>(element));
        }
    );
}
