#include "TimeCycleProcessor.hpp"

#include <QDebug>

#include "src/engine/processing/BuildingProcessor.hpp"
#include "src/engine/processing/CharacterProcessor.hpp"
#include "src/defines.hpp"

const qreal MSEC_PER_SEC(1000);



TimeCycleProcessor::TimeCycleProcessor(QObject* parent, const CycleDate& startingDate, const qreal speedRatio) :
    QObject(parent),
    paused(false),
    speedRatio(speedRatio),
    clock(),
    currentCycleDate(startingDate),
    buildingProcessor(new BuildingProcessor(this)),
    characterProcessor(new CharacterProcessor(this))
{
    clock.start(MSEC_PER_SEC / (CYCLE_PER_SECOND * speedRatio), this);
}



qreal TimeCycleProcessor::getSpeedRatio() const
{
    return speedRatio;
}



const CycleDate& TimeCycleProcessor::getCurrentDate() const
{
    return currentCycleDate;
}



void TimeCycleProcessor::registerBuilding(ProcessableBuilding* building)
{
    buildingProcessor->registerBuilding(building);
}



void TimeCycleProcessor::registerCharacter(Character* character)
{
    characterProcessor->registerCharacter(character);
}



void TimeCycleProcessor::unregisterBuilding(ProcessableBuilding* building)
{
    buildingProcessor->unregisterBuilding(building);
}



void TimeCycleProcessor::unregisterCharacter(Character* character)
{
    characterProcessor->unregisterCharacter(character);
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
    auto previousMonth(currentCycleDate.getMonth());

    // Increment to cycle date.
    ++currentCycleDate;
    qDebug() << "Process time-cycle" << currentCycleDate.toString();

    // Process characters.
    characterProcessor->process(currentCycleDate);

    // Process buildings.
    buildingProcessor->process(currentCycleDate);

    emit processFinished();
    if (previousMonth != currentCycleDate.getMonth()) {
        emit dateChanged(currentCycleDate.getYear(), currentCycleDate.getMonth());
    }
}
