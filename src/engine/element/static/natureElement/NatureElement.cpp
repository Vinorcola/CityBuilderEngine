#include "NatureElement.hpp"



NatureElement::NatureElement(const NatureElementInformation& conf, const MapArea& area) :
    state(conf, area)
{

}



NatureElementState NatureElement::getState() const
{
    return state;
}
