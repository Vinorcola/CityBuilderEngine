#ifndef ABSTRACTPROCESSABLE
#define ABSTRACTPROCESSABLE

#include <QtCore/QObject>

class CycleDate;

/**
 * @brief Represent a processable object.
 *
 * A processable object is an object that can be processed by the TimeCycleProcessor (the engine processor).
 *
 * The init() method is called when the object is first registered in the engine processor. Then, the process() method
 * is called on every single time-cycle.
 */
class AbstractProcessable : public QObject
{
        Q_OBJECT

    public:
        AbstractProcessable(QObject* parent);

        /**
         * @brief Init the processable element with the current date.
         */
        virtual void init(const CycleDate& /*date*/) {}

        /**
         * @brief Process a single time-cycle.
         */
        virtual void process(const CycleDate& date) = 0;
};

#endif // ABSTRACTPROCESSABLE
