#include "RandomWalker.hpp"

#include <QDebug>





RandomWalker::RandomWalker(const MapCoordinates& initialLocation) :
    AbstractCharacter(initialLocation)
{
    qDebug() << "Create random walker at" << initialLocation.toString();
}





MapCoordinates RandomWalker::getNextTargetLocation()
{
    return MapCoordinates(1, 5);
}
