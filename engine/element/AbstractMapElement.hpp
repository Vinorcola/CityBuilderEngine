#ifndef ABSTRACTMAPELEMENT_HPP
#define ABSTRACTMAPELEMENT_HPP

#include "engine/map/Map.hpp"





class AbstractMapElement
{
    private:
        Map& map;



    public:
        AbstractMapElement(Map& map);
        virtual ~AbstractMapElement();
};

#endif // ABSTRACTMAPELEMENT_HPP
