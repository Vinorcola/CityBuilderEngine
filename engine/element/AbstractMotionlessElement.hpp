#ifndef ABSTRACTMOTIONLESSELEMENT_HPP
#define ABSTRACTMOTIONLESSELEMENT_HPP

#include "engine/element/AbstractMapElement.hpp"





class AbstractMotionlessElement : public AbstractMapElement
{
    protected:
        MapArea area;



    public:
        AbstractMotionlessElement(Map& map, const MapArea& area);



        const MapArea& getArea() const;
};

#endif // ABSTRACTMOTIONLESSELEMENT_HPP
