#include "TimeCycleProcessor.hpp"

#include <QDebug>

#include "engine/processing/AbstractProcessable.hpp"



const float MSEC_PER_SEC(1000);





TimeCycleProcessor::TimeCycleProcessor(QObject* parent, const float speedRatio) :
    QObject(parent),
    cyclePerSecondBase(2), // 30
    speedRatio(speedRatio),
    clock(),
    processableList(),
    waitingForRegistrationList(),
    waitingForUnregistrationList(),
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
    waitingForRegistrationList.append(processable);
    processable->init(currentCycleDate);
}





void TimeCycleProcessor::unregisterProcessable(AbstractProcessable* processable)
{
    waitingForUnregistrationList.append(processable);
}




void TimeCycleProcessor::timerEvent(QTimerEvent* /*event*/)
{
    qDebug() << "Process time-cycle" << currentCycleDate.toString();

    // Process current processable list.
    for (auto processable : processableList)
    {
        processable->process(currentCycleDate);
    }

    // Process unregistration.
    for (auto processable : waitingForUnregistrationList)
    {
        processableList.removeOne(processable);
    }
    waitingForUnregistrationList.clear();

    // Process registration.
    processableList.append(waitingForRegistrationList);
    waitingForRegistrationList.clear();

    // Increment to cycle date.
    ++currentCycleDate;
    emit processFinished();
}
