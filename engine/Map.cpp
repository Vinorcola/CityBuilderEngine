#include "Map.hpp"

#include <QDebug>

#include "engine/buildings/AbstractBuilding.hpp"
#include "engine/characters/AbstractCharacter.hpp"





Map::Map(const QSize size) :
    QObject(),
    cyclePerSecondBase(1), // 75,
    numberOfCycleBetweenCleans(cyclePerSecondBase * 3),
    size(size),
    processableList(),
    buildingList(),
    cycleRatio(1),
    cycleClock(),
    numberOfCyclesElapsed(0),
    roadGraphNodeList()
{
    cycleClock.start(MSEC_PER_SEC / (cyclePerSecondBase * cycleRatio), this);
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





void Map::setSpeedRatio(const float ratio)
{
    if (ratio >= 0.1 && ratio <= 1.0 && ratio != cycleRatio)
    {
        cycleRatio = ratio;
        
        // Re-launch the timer with the new speed.
        cycleClock.stop();
        cycleClock.start(MSEC_PER_SEC / (cyclePerSecondBase * cycleRatio), this);
    }
}





void Map::registerBuilding(AbstractBuilding* building) throw (InvalidMapElementException)
{
    // Check if the building area is valid.
    if (!isValidArea(building->getArea()))
    {
        throw new InvalidMapElementException(building->getArea());
    }
    
    // Set default entry point to the building.
    building->setEntryPoint(fetchRoadGraphNodeArround(building->getArea()));
    
    // Everything is good. We register the building.
    processableList.append(building);
    buildingList.append(building);
}





void Map::registerCharacter(AbstractCharacter* character)
{
    processableList.append(character);
}





void Map::removeProcessable(Processable* processable)
{
    processableList.removeAt(processableList.indexOf(processable));
    
    AbstractBuilding* building(dynamic_cast<AbstractBuilding*>(processable));
    if (building != nullptr)
    {
        buildingList.removeAt(buildingList.indexOf(building));
    }
}





RoadGraphNode* Map::fetchRoadGraphNodeAt(const MapCoordinates& coordinates)
{
    for (auto node : roadGraphNodeList)
    {
        if (node->getCoordinates() == coordinates)
        {
            return node;
        }
    }
    
    return nullptr;
}





void Map::timerEvent(QTimerEvent* /*event*/)
{
    qDebug() << "Process time-cycle" << numberOfCyclesElapsed;
    
    if (numberOfCyclesElapsed % numberOfCycleBetweenCleans == 0)
    {
        qDebug() << "  - Cleaning";
        for (auto building : buildingList)
        {
            building->clean();
        }
    }
    
    for (auto processable : processableList)
    {
        processable->process();
    }
    ++numberOfCyclesElapsed;
}





RoadGraphNode* Map::fetchRoadGraphNodeArround(const MapArea& area)
{
    // Fetch a road node arround the building starting at the coordinates at north of left point of the area covered by
    // the building. The algorithm turn arround the area following clockwise.
    
    const MapCoordinates& left(area.getLeft());
    MapCoordinates right(area.getRight());
    int moveX(1);
    int moveY(0);
    
    MapCoordinates coordinates(left.getNorth());
    RoadGraphNode* node(fetchRoadGraphNodeAt(coordinates));
    while (node == nullptr)
    {
        coordinates.setX(coordinates.getX() + moveX);
        coordinates.setY(coordinates.getY() + moveY);
        
        if (moveX == 1 && coordinates.getX() > right.getX())
        {
            // Overstep top corner.
            moveX = 0;
            moveY = 1;
        }
        else if (moveY == 1 && coordinates.getY() > right.getY())
        {
            // Overstep right corner.
            moveX = -1;
            moveY = 0;
        }
        else if (moveX == -1 && coordinates.getX() < left.getX())
        {
            // Overstep bottom corner.
            moveY = -1;
            moveX = 0;
        }
        else if (moveY == -1 && coordinates.getY() < left.getY())
        {
            // Overstep left corner. No node found.
            return node; // nulptr
        }
        else
        {
            node = fetchRoadGraphNodeAt(coordinates);
        }
    }
    
    return node;
}
