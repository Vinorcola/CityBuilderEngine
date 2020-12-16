#include "NatureElement.hpp"



NatureElement::NatureElement(const NatureElementInformation& conf, const TileArea& area) :
    state(reinterpret_cast<qintptr>(this), conf, area)
{

}



NatureElementState NatureElement::getState() const
{
    return state;
}
