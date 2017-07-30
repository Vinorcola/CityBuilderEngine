#include "TimeCycleProcessor.hpp"

#include <QDebug>

#include "defines.hpp"
#include "engine/element/dynamic/AbstractDynamicMapElement.hpp"
#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"
#include "engine/processing/AbstractProcessable.hpp"

const qreal MSEC_PER_SEC(1000);



TimeCycleProcessor::TimeCycleProcessor(QObject* parent, const qreal speedRatio) :
    QObject(parent),
    speedRatio(speedRatio),
    clock(),
    processableList(),
    waitingForRegistrationList(),
    waitingForUnregistrationList(),
    currentCycleDate()
{
    clock.start(MSEC_PER_SEC / (CYCLE_PER_SECOND * speedRatio), this);
}



void TimeCycleProcessor::setSpeedRatio(const qreal ratio)
{
    if (ratio >= 0.1 && ratio <= 1.0 && ratio != speedRatio) {
        speedRatio = ratio;

        // Re-launch the timer with the new speed.
        clock.stop();
        clock.start(MSEC_PER_SEC / (CYCLE_PER_SECOND * ratio), this);
    }
}



void TimeCycleProcessor::registerProcessable(AbstractProcessable* processable)
{
    waitingForRegistrationList.append(processable);
}



void TimeCycleProcessor::unregisterProcessable(AbstractProcessable* processable)
{
    waitingForUnregistrationList.append(processable);
}


void TimeCycleProcessor::timerEvent(QTimerEvent* /*event*/)
{
    processCycle();
}



void TimeCycleProcessor::processCycle()
{
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
    for (auto processable: waitingForUnregistrationList) {
        processableList.removeOne(processable);
    }
    waitingForUnregistrationList.clear();

    // Process registration.
    for (auto processable: waitingForRegistrationList) {
        if (processable) {
            processable->init(currentCycleDate);
            processableList.append(processable);
        }
    }
    waitingForRegistrationList.clear();

    // Increment to cycle date.
    ++currentCycleDate;
    emit processFinished();
}
