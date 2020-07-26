#include "AbstractWalkerGenerator.hpp"

#include "src/engine/element/static/ProcessableBuilding.hpp"



AbstractWalkerGenerator::AbstractWalkerGenerator(
    ProcessableBuilding* issuer,
    const CharacterInformation* walkerConf,
    const int generationInterval,
    const int maxWalkers
) :
    AbstractActivityBehavior(issuer),
    issuer(issuer),
    walkerConf(walkerConf),
    generationInterval(generationInterval),
    maxWalkers(maxWalkers),
    needToSetupNextGenerationDate(true),
    nextGenerationDate()
{

}



bool AbstractWalkerGenerator::contains(const Character* walker) const
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
    if (activitySpeedRatio == ratio) {
        return;
    }

    if (ratio <= 0.0) {
        activitySpeedRatio = 0.0;
        nextGenerationDate.reset();
    } else {
        if (ratio > 1.0) {
            ratio = 1.0;
        }

        // Calculate the next generation date and setup ratio.
        if (nextGenerationDate) {
            int dateInterval(nextGenerationDate - currentDate);
            nextGenerationDate.reassign(currentDate, dateInterval * ratio / activitySpeedRatio);
            activitySpeedRatio = ratio;
        } else if (activitySpeedRatio == 0.0) {
            activitySpeedRatio = ratio;
            setupNextGenerationDate(currentDate);
        }
    }
}



bool AbstractWalkerGenerator::acceptItem(const ItemInformation* /*itemType*/) const
{
    return false;
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



bool AbstractWalkerGenerator::processInteraction(const CycleDate& date, Character* actor)
{
    // Process a random walker issued from this walker generator.
    if (contains(actor)) {
        emit requestDynamicElementDestruction(actor, [this, date]() {
            clean();
        });

        return true;
    }

    return false;
}



bool AbstractWalkerGenerator::canSetupNextGenerationDate(const CycleDate& currentDate) const
{
    return
        activitySpeedRatio > 0.0 &&
        walkers.size() < maxWalkers &&
        nextGenerationDate <= currentDate;
}



void AbstractWalkerGenerator::setupNextGenerationDate(const CycleDate& currentDate)
{
    if (canSetupNextGenerationDate(currentDate)) {
        nextGenerationDate.reassign(currentDate, generationInterval * activitySpeedRatio);
    }

    needToSetupNextGenerationDate = false;
}



void AbstractWalkerGenerator::generate()
{
    emit requestDynamicElementCreation(
        walkerConf,
        issuer,
        [this](Character* element) {
            walkers.append(element);
        }
    );
}
