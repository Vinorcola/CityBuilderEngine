#include "TimeCycleProcessor.hpp"

#include <QDebug>

#include "defines.hpp"
#include "engine/element/AbstractDynamicMapElement.hpp"
#include "engine/element/building/AbstractProcessableBuilding.hpp"
#include "engine/processing/AbstractProcessable.hpp"

const qreal MSEC_PER_SEC(1000);



TimeCycleProcessor::TimeCycleProcessor(QObject* parent, const qreal speedRatio) :
    QObject(parent),
    speedRatio(speedRatio),
    clock(),
    dynamicProcessableList(),
    staticProcessableList(),
    waitingForRegistrationList(),
    dynamicWaitingForUnregistrationList(),
    staticWaitingForUnregistrationList(),
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
    if (dynamic_cast<AbstractProcessableBuilding*>(processable)) {
        staticWaitingForUnregistrationList.append(processable);
    } else if (dynamic_cast<AbstractDynamicMapElement*>(processable)) {
        dynamicWaitingForUnregistrationList.append(processable);
    }
}


void TimeCycleProcessor::timerEvent(QTimerEvent* /*event*/)
{
    qDebug() << "Process time-cycle" << currentCycleDate.toString();

    // Process current processable list.
    // Dynamic elements have to be processed first has some of them may be deleted by the process of a static element.
    for (auto processable : dynamicProcessableList) {
        processable->process(currentCycleDate);
    }
    for (auto processable : staticProcessableList) {
        processable->process(currentCycleDate);
    }

    // Process unregistration.
    for (auto processable : dynamicWaitingForUnregistrationList) {
        dynamicProcessableList.removeOne(processable);
    }
    dynamicWaitingForUnregistrationList.clear();
    for (auto processable : staticWaitingForUnregistrationList) {
        staticProcessableList.removeOne(processable);
    }
    staticWaitingForUnregistrationList.clear();

    // Process registration.
    for (auto processable : waitingForRegistrationList) {
        processable->init(currentCycleDate);
        if (dynamic_cast<AbstractProcessableBuilding*>(processable)) {
            staticProcessableList.append(processable);
        } else if (dynamic_cast<AbstractDynamicMapElement*>(processable)) {
            dynamicProcessableList.append(processable);
        }
    }
    waitingForRegistrationList.clear();

    // Increment to cycle date.
    ++currentCycleDate;
    emit processFinished();
}
