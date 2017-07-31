#include "AbstractStaticMapElement.hpp"





AbstractStaticMapElement::AbstractStaticMapElement(const StaticElementInformation* conf, const MapArea& area) :
    AbstractMapElement(),
    conf(conf),
    area(area)
{

}



const StaticElementInformation*AbstractStaticMapElement::getConf() const
{
    return conf;
}





const MapArea& AbstractStaticMapElement::getArea() const
{
    return area;
}
