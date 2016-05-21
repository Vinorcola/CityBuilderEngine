#ifndef TIMECYCLEPROCESSOR_HPP
#define TIMECYCLEPROCESSOR_HPP

#include <QBasicTimer>
#include <QList>
#include <QObject>

#include "engine/processing/CycleDate.hpp"

class AbstractProcessable;





/**
 * @brief Class handling the time-cycle loop.
 *
 * The time-cycle loop is the loop that make the game running. It process the evolution of each element on the map. The
 * normal speed (100%) implies 75 cycles per second. The speed can be lower down, down to 10% (then, only 7.5 cycles are
 * processed each seconds).
 *
 * @todo A no-limit speed could be eventually set, making the next cycle begin as soon as the current cycle ends.
 */
class TimeCycleProcessor : public QObject
{
        Q_OBJECT

    private:
        const float cyclePerSecondBase;

        float speedRatio;
        QBasicTimer clock;
        QList<AbstractProcessable*> processableList;
        CycleDate currentCycleDate;



    public:
        TimeCycleProcessor(const float speedRatio = 1.0);



        /**
         * @brief Change the speed ratio of the time-cycle loop.
         *
         * @param ratio A ratio between 0.1 and 1.
         */
        void setSpeedRatio(const float ratio);
        void registerProcessable(AbstractProcessable* processable);
        void unregisterProcessable(AbstractProcessable* processable);



    protected:
        virtual void timerEvent(QTimerEvent* event);
};

#endif // TIMECYCLEPROCESSOR_HPP