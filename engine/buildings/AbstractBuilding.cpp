#include "AbstractBuilding.hpp"





AbstractBuilding::AbstractBuilding(const MapArea& location, const int maxNumberOfWorkers, const int maxNumberOfWalkers) :
    Processable(),
    maxNumberOfWorkers(maxNumberOfWorkers),
    maxNumberOfWalkers(maxNumberOfWalkers),
    location(location),
    currentNumberOfWorkers(0),
    currentWalkers()
{
    
}





int AbstractBuilding::getMaxNumberOfWorkers() const
{
    return maxNumberOfWorkers;
}





int AbstractBuilding::getMaxNumberOfWalkers() const
{
    return maxNumberOfWalkers;
}





int AbstractBuilding::getCurrentNumberOfWorkers() const
{
    return currentNumberOfWorkers;
}





int AbstractBuilding::getCurrentNumberOfWalkers() const
{
    return currentWalkers.size();
}





void AbstractBuilding::setCurrentNumberOfWorkers(const int numberOfWorkers) throw(OutOfRangeException)
{
    if (numberOfWorkers < 0 || numberOfWorkers > maxNumberOfWorkers)
    {
        throw OutOfRangeException("Trying to set number of workers (" + QString::number(numberOfWorkers) + ") higher than max accepted workers (" + QString::number(maxNumberOfWorkers) + ")");
    }
    this->currentNumberOfWorkers = numberOfWorkers;
}





int AbstractBuilding::registerWalker(AbstractCharacter* walker)
{
    currentWalkers.append(walker);
    return currentWalkers.size();
}
