#include "Map.hpp"

#include "engine/element/AbstractMotionlessElement.hpp"





Map::Map(const QSize& size) :
    size(size),
    roadGraph(),
    processor(),
    elementList()
{

}





bool Map::isValidCoordinates(const MapCoordinates& coordinates) const
{
    int sum(coordinates.getY() + coordinates.getX());
    int diff(coordinates.getY() - coordinates.getX());
    return diff >= 0 && diff < size.height()
            && sum >= 0 && sum < size.width();
}





bool Map::isValidArea(const MapArea& area) const
{
    return isValidCoordinates(area.getLeft())
        && isValidCoordinates(area.getRight())
        && isValidCoordinates(area.getTop())
            && isValidCoordinates(area.getBottom());
}





bool Map::isFreeCoordinates(const MapCoordinates& coordinates) const
{
    for (auto element : elementList)
    {
        AbstractMotionlessElement* motionlessElement(dynamic_cast<AbstractMotionlessElement*>(element));
        if (motionlessElement)
        {
            if (motionlessElement->getArea().isInside(coordinates))
            {
                return false;
            }
        }
    }

    return true;
}





bool Map::isFreeArea(const MapArea& area) const
{
    auto left(area.getLeft());
    auto right(area.getRight());

    MapCoordinates coordinates(left);
    while (coordinates.getX() <= right.getX())
    {
        while (coordinates.getY() <= right.getY())
        {
            if (!isFreeCoordinates(coordinates))
            {
                return false;
            }
            coordinates = coordinates.getEast();
        }
        coordinates = MapCoordinates(coordinates.getX() + 1, left.getY());
    }

    return true;
}





void Map::registerElement(AbstractMapElement* element)
{
    AbstractMotionlessElement* motionlessElement(dynamic_cast<AbstractMotionlessElement*>(element));
    if (motionlessElement != nullptr)
    {
        if (!isFreeArea(motionlessElement->getArea()))
        throw new UnexpectedException("Try to create a motionless element on an occupyed area " + motionlessElement->getArea().toString());
    }
    elementList.append(element);
}





void Map::unregisterElement(AbstractMapElement* element)
{
    elementList.removeOne(element);
}





RoadGraph& Map::getRoadGraph()
{
    return roadGraph;
}





TimeCycleProcessor& Map::getProcessor()
{
    return processor;
}
