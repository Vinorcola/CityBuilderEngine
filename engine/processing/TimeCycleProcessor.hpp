#ifndef TIMECYCLEPROCESSOR_HPP
#define TIMECYCLEPROCESSOR_HPP

#include <QtCore/QBasicTimer>
#include <QtCore/QLinkedList>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QPointer>

#include "engine/processing/AbstractProcessable.hpp"
#include "engine/processing/CycleDate.hpp"

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

    private:
        bool paused;
        qreal speedRatio;
        QBasicTimer clock;
        QLinkedList<QPointer<AbstractProcessable>> processableList;
        QList<QPointer<AbstractProcessable>> waitingForRegistrationList;
        QList<AbstractProcessable*> waitingForUnregistrationList;
        CycleDate currentCycleDate;

    public:
        TimeCycleProcessor(QObject* parent, const qreal speedRatio = 1.0);

        /**
         * @brief Register a processable element.
         *
         * @param processable
         */
        void registerProcessable(AbstractProcessable* processable);

        /**
         * @brief Unregister a processable element.
         *
         * @param processable
         */
        void unregisterProcessable(AbstractProcessable* processable);

        qreal getSpeedRatio() const;

    public slots:
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
};

#endif // TIMECYCLEPROCESSOR_HPP
