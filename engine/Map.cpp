#include "Map.hpp"

#include <QDebug>





Map::Map(const QSize size) :
    QObject(),
    size(size),
    processableList(),
    cyclePerSecondBase(1), // 75
    cycleRatio(1),
    cycleClock()
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





void Map::timerEvent(QTimerEvent* /*event*/)
{
    qDebug() << "Process a time-cycle";
    
    for (auto processable : processableList)
    {
        processable->process();
    }
}
