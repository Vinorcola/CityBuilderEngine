#ifndef ABSTRACTACTIVITYBEHAVIOR_HPP
#define ABSTRACTACTIVITYBEHAVIOR_HPP

#include "engine/element/static/behavior/AbstractStaticElementBehavior.hpp"

class AbstractActivityBehavior : public AbstractStaticElementBehavior
{
        Q_OBJECT

    public:
        AbstractActivityBehavior(QObject* parent);

        virtual void setActivitySpeedRatio(qreal ratio, const CycleDate& currentDate) = 0;
};

#endif // ABSTRACTACTIVITYBEHAVIOR_HPP
