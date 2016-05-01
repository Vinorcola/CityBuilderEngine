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
    numberOfCyclesElapsed(0)
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





void Map::registerBuilding(AbstractBuilding* building)
{
    // TODO: Check if building area is valid.
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
