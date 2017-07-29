#include "AbstractCharacter.hpp"



AbstractCharacter::AbstractCharacter(QWeakPointer<AbstractProcessableBuilding> issuer, const qreal speed) :
    AbstractDynamicMapElement(issuer, speed)
{

}
