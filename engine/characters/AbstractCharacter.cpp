#include "AbstractCharacter.hpp"





AbstractCharacter::AbstractCharacter(Map* map) :
    Processable(map),
    alive(true)
{
    map->registerCharacter(this);
}





bool AbstractCharacter::isAlive() const
{
    return alive;
}





void AbstractCharacter::kill()
{
    alive = false;
}
