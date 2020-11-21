#include "NatureElement.hpp"



NatureElement::NatureElement(const NatureElementInformation& conf, const MapArea& area) :
    state(reinterpret_cast<qintptr>(this), conf, area)
{

}



NatureElementState NatureElement::getState() const
{
    return state;
}
