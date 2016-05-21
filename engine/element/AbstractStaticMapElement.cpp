#include "AbstractStaticMapElement.hpp"





AbstractStaticMapElement::AbstractStaticMapElement(const MapArea& area) :
    area(area)
{

}





const MapArea& AbstractStaticMapElement::getArea() const
{
    return area;
}
