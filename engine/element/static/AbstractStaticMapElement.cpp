#include "AbstractStaticMapElement.hpp"





AbstractStaticMapElement::AbstractStaticMapElement(const MapArea& area) :
    AbstractMapElement(),
    area(area)
{

}





const MapArea& AbstractStaticMapElement::getArea() const
{
    return area;
}
