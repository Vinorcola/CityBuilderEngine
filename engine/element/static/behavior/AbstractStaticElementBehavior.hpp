#ifndef ABSTRACTSTATICELEMENTBEHAVIOR_HPP
#define ABSTRACTSTATICELEMENTBEHAVIOR_HPP

#include "engine/processing/AbstractProcessable.hpp"

class AbstractDynamicMapElement;
class CycleDate;

class AbstractStaticElementBehavior : public AbstractProcessable
{
        Q_OBJECT

    public:
        AbstractStaticElementBehavior(QObject* parent);

        virtual bool processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor) = 0;

        virtual void setActivitySpeedRatio(qreal ratio, const CycleDate& currentDate) = 0;
};

#endif // ABSTRACTSTATICELEMENTBEHAVIOR_HPP
