#ifndef TIMECYCLEPROCESSOR_HPP
#define TIMECYCLEPROCESSOR_HPP

#include <QBasicTimer>
#include <QLinkedList>
#include <QList>
#include <QObject>
#include <QWeakPointer>

#include "engine/processing/AbstractProcessable.hpp"
#include "engine/processing/CycleDate.hpp"

/**
 * @brief Class handling the time-cycle loop.
 *
 * The time-cycle loop is the loop that make the game running. It process the evolution of each element on the map. The
 * normal speed (100%) implies 75 cycles per second. The speed can be lower down to 10% (then, only 7.5 cycles are
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
        QLinkedList<QWeakPointer<AbstractProcessable>> processableList;
        QList<QWeakPointer<AbstractProcessable>> waitingForRegistrationList;
        QList<QWeakPointer<AbstractProcessable>> waitingForUnregistrationList;
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
        void registerProcessable(QWeakPointer<AbstractProcessable> processable);

        /**
         * @brief Unregister a processable element.
         *
         * @param processable
         */
        void unregisterProcessable(QWeakPointer<AbstractProcessable> processable);

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
};

#endif // TIMECYCLEPROCESSOR_HPP
