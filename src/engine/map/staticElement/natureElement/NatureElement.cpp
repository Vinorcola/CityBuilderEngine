#include "NatureElement.hpp"

#include "src/global/state/NatureElementState.hpp"



NatureElement::NatureElement(const NatureElementInformation& conf, const TileArea& area) :
    AbstractStaticElement(),
    conf(conf),
    area(area),
    busy(false)
{

}



const NatureElementInformation& NatureElement::getConf() const
{
    return conf;
}



const TileArea& NatureElement::getArea() const
{
    return area;
}



void NatureElement::startInteraction()
{
    busy = true;
}



void NatureElement::endInteraction()
{
    busy = false;
}



bool NatureElement::isBusy() const
{
    return busy;
}



NatureElementState NatureElement::getState() const
{
    return { reinterpret_cast<qintptr>(this), conf, area };
}
