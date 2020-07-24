#include "ConditionalRandomWalkerGenerator.hpp"

#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"



ConditionalRandomWalkerGenerator::ConditionalRandomWalkerGenerator(
    AbstractProcessableStaticMapElement* issuer,
    const CharacterInformation* walkerConf,
    const CharacterInformation* dependencyWalkerConf,
    const int generationInterval,
    const int maxWalkers
) :
    RandomWalkerGenerator(issuer, walkerConf, generationInterval, maxWalkers),
    dependencyWalkerConf(dependencyWalkerConf),
    activityInterval(generationInterval * 3),
    canGenarateWalkerUntilDate()
{

}



void ConditionalRandomWalkerGenerator::process(const CycleDate& date)
{
    if (date == canGenarateWalkerUntilDate) {
        nextGenerationDate.reset();
    }

    RandomWalkerGenerator::process(date);
}



bool ConditionalRandomWalkerGenerator::processInteraction(const CycleDate& date, Character* actor)
{
    if (RandomWalkerGenerator::processInteraction(date, actor)) {
        return true;
    }

    // Process a walker that is needed to generate random walkers.
    if (actor->getConf() == dependencyWalkerConf) {
        canGenarateWalkerUntilDate.reassign(date, activityInterval);
        if (nextGenerationDate < date) {
            setupNextGenerationDate(date);
        }
        auto issuer(actor->getIssuer());
        emit requestDynamicElementDestruction(actor, [this, date, issuer]() {
            if (issuer) {
                issuer->notifyWalkerDestruction();
            }
        });

        return true;
    }

    return false;
}



bool ConditionalRandomWalkerGenerator::canSetupNextGenerationDate(const CycleDate& currentDate) const
{
    return
        currentDate <= canGenarateWalkerUntilDate &&
        RandomWalkerGenerator::canSetupNextGenerationDate(currentDate);
}
