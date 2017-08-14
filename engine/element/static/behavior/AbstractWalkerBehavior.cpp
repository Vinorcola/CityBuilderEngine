#include "AbstractWalkerBehavior.hpp"

#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"



AbstractWalkerBehavior::AbstractWalkerBehavior(AbstractProcessableStaticMapElement* issuer) :
    AbstractStaticElementBehavior(issuer),
    issuer(issuer)
{

}
