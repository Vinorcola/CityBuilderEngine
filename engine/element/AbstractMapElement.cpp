#include "AbstractMapElement.hpp"





AbstractMapElement::AbstractMapElement(Map& map) :
    map(map)
{
    map.registerElement(this);
}





AbstractMapElement::~AbstractMapElement()
{
    map.unregisterElement(this);
}
