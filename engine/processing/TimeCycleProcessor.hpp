#ifndef TIMECYCLEPROCESSOR_HPP
#define TIMECYCLEPROCESSOR_HPP

#include <QBasicTimer>
#include <QLinkedList>
#include <QList>
#include <QObject>
#include <QPointer>

#include "engine/processing/AbstractProcessable.hpp"
#include "engine/processing/CycleDate.hpp"

/**
 * @brief A processor that process all the processable elements on each time-cycle.
 *
 * The time-cycle loop is the loop that make the game running. It process the evolution of each processable object. The
 * normal speed (100%) implies 30 cycles per second. The speed can be lower down to 10% (then, only 3 cycles are
 * processed each seconds).
 *
 * @todo A no-limit speed could be eventually set, making the next cycle begin as soon as the current cycle ends.
 */
class TimeCycleProcessor : public QObject
{
        Q_OBJECT

    private:
        qreal speedRatio;
        QBasicTimer clock;
        QLinkedList<QPointer<AbstractProcessable>> processableList;
        QList<QPointer<AbstractProcessable>> waitingForRegistrationList;
        QList<AbstractProcessable*> waitingForUnregistrationList;
        CycleDate currentCycleDate;

    public:
        TimeCycleProcessor(QObject* parent, const qreal speedRatio = 1.0);

        /**
         * @brief Change the speed ratio of the time-cycle loop.
         *
         * @param ratio A ratio between 0.1 and 1.
         */
        void setSpeedRatio(const qreal ratio);

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
