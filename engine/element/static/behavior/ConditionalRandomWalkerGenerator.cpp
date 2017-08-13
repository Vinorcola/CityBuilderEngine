#include "ConditionalRandomWalkerGenerator.hpp"

#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"



ConditionalRandomWalkerGenerator::ConditionalRandomWalkerGenerator(
    QObject* parent,
    const DynamicElementInformation* walkerConf,
    const DynamicElementInformation* dependencyWalkerConf,
    const int generationInterval,
    const int maxWalkers
) :
    RandomWalkerGenerator(parent, walkerConf, generationInterval, maxWalkers),
    dependencyWalkerConf(dependencyWalkerConf),
    activityInterval(dependencyWalkerConf->getWalkingCredit() * 2),
    canGenarateWalkerUntilDate()
{

}



void ConditionalRandomWalkerGenerator::process(const CycleDate& date)
{
    if (date == canGenarateWalkerUntilDate) {
        setGenerationSpeedRatio(0.0, date);
    }

    RandomWalkerGenerator::process(date);
}



bool ConditionalRandomWalkerGenerator::processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor)
{
    if (RandomWalkerGenerator::processInteraction(date, actor)) {
        return true;
    }

    // Process a walker that is needed to generate random walkers.
    if (actor->getConf() == dependencyWalkerConf) {
        setGenerationSpeedRatio(1.0, date);
        canGenarateWalkerUntilDate.reassign(date, activityInterval);
        auto issuer(actor->getIssuer());
        emit requestDynamicElementDestruction(actor, [this, date, issuer]() {
            if (issuer) {
                issuer->notifyWalkerDestruction(date);
            }
        });

        return true;
    }

    return false;
}
