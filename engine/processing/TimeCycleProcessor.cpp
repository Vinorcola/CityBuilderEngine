#include "TimeCycleProcessor.hpp"

#include <QDebug>

#include "engine/processing/AbstractProcessable.hpp"



const float MSEC_PER_SEC(1000);





TimeCycleProcessor::TimeCycleProcessor(const float speedRatio) :
    cyclePerSecondBase(2), // 75
    speedRatio(speedRatio),
    clock(),
    processableList(),
    currentCycleDate()
{
    clock.start(MSEC_PER_SEC / (cyclePerSecondBase * speedRatio), this);
}





void TimeCycleProcessor::setSpeedRatio(const float ratio)
{
    if (ratio >= 0.1 && ratio <= 1.0 && ratio != speedRatio)
    {
        speedRatio = ratio;

        // Re-launch the timer with the new speed.
        clock.stop();
        clock.start(MSEC_PER_SEC / (cyclePerSecondBase * ratio), this);
    }
}





void TimeCycleProcessor::registerProcessable(AbstractProcessable* processable)
{
    processableList.append(processable);
}





void TimeCycleProcessor::unregisterProcessable(AbstractProcessable* processable)
{
    processableList.removeOne(processable);
}




void TimeCycleProcessor::timerEvent(QTimerEvent* /*event*/)
{
    qDebug() << "Process time-cycle" << currentCycleDate.toString();

    for (auto processable : processableList)
    {
        processable->process();
    }

    ++currentCycleDate;
}
