#include "QueuedWalkerGenerator.hpp"

#include "engine/element/dynamic/Character.hpp"
#include "engine/random.hpp"



QueuedWalkerGenerator::QueuedWalkerGenerator(ProcessableBuilding* issuer,
    const CharacterInformation* walkerConf,
    const int minGenerationInterval,
    const int maxGenerationInterval
) :
    AbstractStaticElementBehavior(issuer),
    issuer(issuer),
    walkerConf(walkerConf),
    minGenerationInterval(minGenerationInterval),
    maxGenerationInterval(maxGenerationInterval),
    nextWalkerGenerationDate(),
    walkerRequestQueue()
{

}



const CharacterInformation* QueuedWalkerGenerator::getWalkerConf() const
{
    return walkerConf;
}



void QueuedWalkerGenerator::process(const CycleDate& date)
{
    if (!walkerRequestQueue.isEmpty()) {
        if (date == nextWalkerGenerationDate) {
            emit requestDynamicElementCreation(
                walkerConf,
                issuer,
                walkerRequestQueue.takeFirst()
            );
            setupNextWalkerGenerationDate(date);
        } else if (date > nextWalkerGenerationDate) {
            setupNextWalkerGenerationDate(date);
        }
    }
}



bool QueuedWalkerGenerator::processInteraction(const CycleDate& /*date*/, Character* /*actor*/)
{
    return false;
}



void QueuedWalkerGenerator::registerWalkerRequest(std::function<void(Character*)> onWalkerCreation)
{
    walkerRequestQueue.append(onWalkerCreation);
}



void QueuedWalkerGenerator::setupNextWalkerGenerationDate(const CycleDate& currentDate)
{
    if (!walkerRequestQueue.isEmpty() && nextWalkerGenerationDate <= currentDate) {
        nextWalkerGenerationDate.reassign(currentDate, randomInt(minGenerationInterval, maxGenerationInterval));
    }
}
