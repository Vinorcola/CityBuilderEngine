#include "AbstractBuilding.hpp"





AbstractBuilding::AbstractBuilding(const MapArea& location, const int maxWorkers) :
    Processable(),
    maxWorkers(maxWorkers),
    currentWorkers(0),
    location(location)
{
    
}





int AbstractBuilding::getMaxWorkers() const
{
    return maxWorkers;
}





int AbstractBuilding::getCurrentWorkers() const
{
    return currentWorkers;
}





void AbstractBuilding::setCurrentWorkers(const int workers) throw(OutOfRangeException)
{
    if (workers < 0 || workers > maxWorkers)
    {
        throw OutOfRangeException("Trying to set number of workers (" + QString::number(workers) + ") higher than max accepted workers (" + QString::number(maxWorkers) + ")");
    }
}
