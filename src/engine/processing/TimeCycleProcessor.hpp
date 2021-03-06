#ifndef TIMECYCLEPROCESSOR_HPP
#define TIMECYCLEPROCESSOR_HPP

#include <QtCore/QBasicTimer>
#include <QtCore/QList>
#include <QtCore/QObject>

#include "src/engine/processing/CycleDate.hpp"

class AbstractProcessable;
class Character;

/**
 * @brief An engine processor that process all the processable elements on each time-cycle.
 *
 * The time-cycle loop is the loop that make the game running. It process the evolution of each processable object
 * (AbstractProcessable). The normal speed (100%) implies 30 cycles per second. The speed can be lower down to 10%
 * (then, only 3 cycles are processed each seconds).
 *
 * @todo A no-limit speed could be eventually set, making the next cycle to begin as soon as the current cycle ends.
 */
class TimeCycleProcessor : public QObject
{
        Q_OBJECT

    public:
        TimeCycleProcessor(const CycleDate& startingDate, const qreal speedRatio = 1.0);

        qreal getSpeedRatio() const;

        /**
         * @brief Get the current date.
         *
         * Should not be used for inside the engine, but rather for display purpose. Anything that depends on the
         * current date should be an `AbstractProcessable` object, and should be registered using the appropriate
         * register method.
         */
        const CycleDate& getCurrentDate() const;

        void registerProcessable(AbstractProcessable& processable);

        /**
         * @brief Pause (or resume) the time-cycle processor.
         */
        void pause(const bool pause = true);

        /**
         * @brief Change the speed ratio of the time-cycle loop.
         *
         * @param ratio A ratio between 0.1 and 2.
         */
        void setSpeedRatio(const qreal ratio);

        /**
         * @brief Force the next process to occur.
         *
         * This is only for debug prupose. The process will only be triggered if the processor have been paused.
         */
        void forceNextProcess();

    signals:
        /**
         * @brief Indicate when a cycle process is finished.
         */
        void processFinished();

    protected:
        /**
         * @brief Timer event callback.
         *
         * This method is triggered by timer events. It call the AbstractProcessable::process() method of each
         * processable element it is aware of.
         *
         * @param event
         */
        virtual void timerEvent(QTimerEvent* event);

        /**
         * @brief Process a cycle.
         */
        void processCycle();

    private:
        bool paused;
        qreal speedRatio;
        QBasicTimer clock;
        CycleDate currentCycleDate;
        QList<AbstractProcessable*> processableElements;
};

#endif // TIMECYCLEPROCESSOR_HPP
