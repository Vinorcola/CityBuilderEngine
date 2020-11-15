#include "NatureElement.hpp"



NatureElement::NatureElement(const NatureElementInformation& conf, const MapArea& area) :
    conf(conf),
    area(area)
{

}



const NatureElementInformation& NatureElement::getConf() const
{
    return conf;
}



const MapArea& NatureElement::getArea() const
{
    return area;
}
