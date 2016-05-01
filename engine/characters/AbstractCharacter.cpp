#include "AbstractCharacter.hpp"





AbstractCharacter::AbstractCharacter(Map* map, const int speed, const int lifePoints) :
    Processable(map),
    speed(speed),
    lifePoints(lifePoints)
{
    map->registerCharacter(this);
}





bool AbstractCharacter::isAlive() const
{
    return lifePoints > 0;
}





void AbstractCharacter::kill()
{
    lifePoints = 0;
}
