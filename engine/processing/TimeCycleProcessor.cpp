#include "TimeCycleProcessor.hpp"

#include <QDebug>

#include "engine/element/dynamic/Character.hpp"
#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"
#include "engine/processing/AbstractProcessable.hpp"
#include "defines.hpp"

const qreal MSEC_PER_SEC(1000);



TimeCycleProcessor::TimeCycleProcessor(QObject* parent, const qreal speedRatio) :
    QObject(parent),
    paused(false),
    speedRatio(speedRatio),
    clock(),
    processableList(),
    waitingForRegistrationList(),
    waitingForUnregistrationList(),
    currentCycleDate()
{
    clock.start(MSEC_PER_SEC / (CYCLE_PER_SECOND * speedRatio), this);
}



void TimeCycleProcessor::registerProcessable(AbstractProcessable* processable)
{
    waitingForRegistrationList.append(processable);
}



void TimeCycleProcessor::unregisterProcessable(AbstractProcessable* processable)
{
    waitingForUnregistrationList.append(processable);
}



qreal TimeCycleProcessor::getSpeedRatio() const
{
    return speedRatio;
}



void TimeCycleProcessor::pause(const bool pause)
{
    if (pause != paused) {
        paused = pause;
        if (pause) {
            clock.stop();
        } else {
            clock.start(MSEC_PER_SEC / (CYCLE_PER_SECOND * speedRatio), this);
        }
    }
}



void TimeCycleProcessor::setSpeedRatio(const qreal ratio)
{
    if (ratio != speedRatio && ratio >= 0.1 && ratio <= 2.0) {
        speedRatio = ratio;

        if (!paused) {
            // Re-launch the timer with the new speed.
            clock.stop();
            clock.start(MSEC_PER_SEC / (CYCLE_PER_SECOND * ratio), this);
        }
    }
}



void TimeCycleProcessor::forceNextProcess()
{
    if (paused) {
        processCycle();
    }
}



void TimeCycleProcessor::timerEvent(QTimerEvent* /*event*/)
{
    processCycle();
}



void TimeCycleProcessor::processCycle()
{
    // Increment to cycle date.
    ++currentCycleDate;
    qDebug() << "Process time-cycle" << currentCycleDate.toString();

    // Process current processable list.
    for (auto processable: processableList) {
        if (processable) {
            processable->process(currentCycleDate);
        } else {
            waitingForUnregistrationList.append(processable);
        }
    }

    // Process unregistration.
    while (!waitingForUnregistrationList.isEmpty()) {
        processableList.removeOne(waitingForUnregistrationList.takeFirst());
    }

    // Process registration.
    while (!waitingForRegistrationList.isEmpty()) {
        auto processable(waitingForRegistrationList.takeFirst());
        if (processable) {
            processable->init(currentCycleDate);
            processableList.append(processable);
        }
    }

    emit processFinished();
}
