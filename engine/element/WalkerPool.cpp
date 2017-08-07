#include "WalkerPool.hpp"



WalkerPool::WalkerPool(
    QObject* parent,
    const DynamicElementInformation* elementConf,
    const int generationInterval,
    const int max
) : AbstractProcessable(parent),
    elementConf(elementConf),
    generationInterval(generationInterval),
    max(max),
    nextGenerationDate(),
    walkers()
{

}



bool WalkerPool::contains(const TargetedWalker* walker) const
{
    for (auto walkerFromList : walkers) {
        if (walkerFromList == walker) {
            return true;
        }
    }

    return false;
}



void WalkerPool::clean(const CycleDate& currentDate)
{
    auto iterator(walkers.begin());
    while (iterator != walkers.end()) {
        if (iterator->isNull()) {
            iterator = walkers.erase(iterator);
            setupNextWalkerGenerationDate(currentDate);
        } else {
            ++iterator;
        }
    }
}



void WalkerPool::init(const CycleDate& date)
{
    setupNextWalkerGenerationDate(date);
}



void WalkerPool::process(const CycleDate& date)
{
    if (date == nextGenerationDate) {
        processWalkerGeneration(date);
    }
}



void WalkerPool::setupNextWalkerGenerationDate(const CycleDate& currentDate)
{
    if (walkers.size() < max && nextGenerationDate <= currentDate) {
        nextGenerationDate = currentDate;
        nextGenerationDate.add(generationInterval);
    }
}



void WalkerPool::processWalkerGeneration(const CycleDate& currentDate)
{
    emit requestDynamicElementCreation(
        elementConf,
        [this, currentDate](AbstractDynamicMapElement* element) {
            auto walker(dynamic_cast<TargetedWalker*>(element));
            if (walker) {
                walkers.append(walker);
                setupNextWalkerGenerationDate(currentDate);
            }
        }
    );
}
