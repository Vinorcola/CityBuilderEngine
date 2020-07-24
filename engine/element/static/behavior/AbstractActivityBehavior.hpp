#ifndef ABSTRACTACTIVITYBEHAVIOR_HPP
#define ABSTRACTACTIVITYBEHAVIOR_HPP

#include "engine/element/static/behavior/AbstractBehavior.hpp"

/**
 * @brief The base class for behaviors for which the process depends on the building's activity.
 *
 * Buildings that rely on employment will have an activity ratio. This ratio will change according to the building's
 * employment capacity.
 */
class AbstractActivityBehavior : public AbstractBehavior
{
        Q_OBJECT

    public:
        AbstractActivityBehavior(QObject* parent);

        virtual void setActivitySpeedRatio(qreal ratio, const CycleDate& currentDate) = 0;
};

#endif // ABSTRACTACTIVITYBEHAVIOR_HPP
