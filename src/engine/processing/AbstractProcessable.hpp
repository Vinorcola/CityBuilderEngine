#ifndef ABSTRACTPROCESSABLE
#define ABSTRACTPROCESSABLE

#include <QtGlobal>

class CycleDate;

/**
 * @brief Represent a processable object.
 *
 * A processable object is an object that can be processed by the TimeCycleProcessor (the engine processor).
 *
 * The init() method is called when the object is first registered in the engine processor. Then, the process() method
 * is called on every single time-cycle.
 */
class AbstractProcessable
{
        Q_DISABLE_COPY_MOVE(AbstractProcessable)

    public:
        AbstractProcessable();
        virtual ~AbstractProcessable();

        /**
         * @brief Process a single time-cycle.
         */
        virtual void process(const CycleDate& date) = 0;
};

#endif // ABSTRACTPROCESSABLE
