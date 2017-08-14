#include "AbstractWalkerGenerator.hpp"

#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"



AbstractWalkerGenerator::AbstractWalkerGenerator(
    AbstractProcessableStaticMapElement* issuer,
    const DynamicElementInformation* walkerConf,
    const int generationInterval,
    const int maxWalkers
) :
    AbstractStaticElementBehavior(issuer),
    issuer(issuer),
    walkerConf(walkerConf),
    generationInterval(generationInterval),
    maxWalkers(maxWalkers),
    generationSpeedRatio(0.0),
    needToSetupNextGenerationDate(true),
    nextGenerationDate()
{

}



bool AbstractWalkerGenerator::contains(const TargetedWalker* walker) const
{
    for (auto walkerFromList : walkers) {
        if (walkerFromList == walker) {
            return true;
        }
    }

    return false;
}



void AbstractWalkerGenerator::clean()
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



void AbstractWalkerGenerator::setActivitySpeedRatio(qreal ratio, const CycleDate& currentDate)
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



void AbstractWalkerGenerator::process(const CycleDate& date)
{
    if (needToSetupNextGenerationDate) {
        setupNextGenerationDate(date);
    }
    if (date == nextGenerationDate) {
        generate();
        setupNextGenerationDate(date);
    }
}



bool AbstractWalkerGenerator::processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor)
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



bool AbstractWalkerGenerator::canSetupNextGenerationDate(const CycleDate& currentDate) const
{
    return
        generationSpeedRatio > 0.0 &&
        walkers.size() < maxWalkers &&
        nextGenerationDate <= currentDate;
}



void AbstractWalkerGenerator::setupNextGenerationDate(const CycleDate& currentDate)
{
    if (canSetupNextGenerationDate(currentDate)) {
        nextGenerationDate.reassign(currentDate, generationInterval * generationSpeedRatio);
    }

    needToSetupNextGenerationDate = false;
}



void AbstractWalkerGenerator::generate()
{
    emit requestDynamicElementCreation(
        walkerConf,
        issuer,
        [this](AbstractDynamicMapElement* element) {
            walkers.append(static_cast<TargetedWalker*>(element));
        }
    );
}
