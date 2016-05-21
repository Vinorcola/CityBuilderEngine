#include "RandomWalker.hpp"





RandomWalker::RandomWalker(const MapCoordinates& initialLocation) :
    AbstractCharacter(initialLocation)
{

}





MapCoordinates RandomWalker::getNextTargetLocation()
{
    return MapCoordinates();
}
