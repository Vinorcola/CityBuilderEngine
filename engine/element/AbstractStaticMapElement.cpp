#include "AbstractStaticMapElement.hpp"





AbstractStaticMapElement::AbstractStaticMapElement(const MapArea& area) :
    area(area)
{

}





AbstractStaticMapElement::~AbstractStaticMapElement()
{

}





const MapArea& AbstractStaticMapElement::getArea() const
{
    return area;
}
