#include "AbstractBuilding.hpp"

#include <QDebug>
#include <QMutableListIterator>





AbstractBuilding::AbstractBuilding(Map* map, const MapArea& location, const int maxNumberOfWorkers, const int maxNumberOfWalkers) :
    Processable(map),
    maxNumberOfWorkers(maxNumberOfWorkers),
    maxNumberOfWalkers(maxNumberOfWalkers),
    location(location),
    currentNumberOfWorkers(0),
    walkerList()
{
    map->registerBuilding(this);
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
    return walkerList.size();
}





void AbstractBuilding::setCurrentNumberOfWorkers(const int numberOfWorkers) throw(OutOfRangeException)
{
    if (numberOfWorkers < 0 || numberOfWorkers > maxNumberOfWorkers)
    {
        throw OutOfRangeException("Trying to set number of workers (" + QString::number(numberOfWorkers) + ") higher than max accepted workers (" + QString::number(maxNumberOfWorkers) + ")");
    }
    this->currentNumberOfWorkers = numberOfWorkers;
}





void AbstractBuilding::clean()
{
    // Deleting dead walkers.
    QMutableListIterator<AbstractCharacter*> iterator(walkerList);
    while (iterator.hasNext())
    {
        AbstractCharacter* character(iterator.next());
        if (!character->isAlive())
        {
            qDebug() << "  - Deleting a walker.";
            iterator.remove();
            delete character;
        }
    }
}





void AbstractBuilding::registerWalker(AbstractCharacter* walker)
{
    walkerList.append(walker);
}
