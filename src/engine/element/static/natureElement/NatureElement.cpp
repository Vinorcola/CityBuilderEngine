#include "NatureElement.hpp"



NatureElement::NatureElement(QObject *parent, const NatureElementInformation& conf, const MapArea& area) :
    QObject(parent),
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
