#include "AbstractMotionlessElement.hpp"





AbstractMotionlessElement::AbstractMotionlessElement(Map& map, const MapArea& area) :
    AbstractMapElement(map),
    area(area)
{

}





const MapArea&AbstractMotionlessElement::getArea() const
{
    return area;
}
