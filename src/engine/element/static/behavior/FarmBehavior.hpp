#ifndef FARMBEHAVIOR_HPP
#define FARMBEHAVIOR_HPP

#include "src/engine/element/static/behavior/AbstractActivityBehavior.hpp"
#include "src/engine/processing/CycleDate.hpp"

class BehaviorInformation;

class FarmBehavior : public AbstractActivityBehavior
{
        Q_OBJECT

    private:
        const BehaviorInformation* conf;
        CycleDate completeGrowingDate;
        int remainingGrowthInterval;///< This is only used to remember the grown percent in case activity ratio goes down to 0.

    public:
        FarmBehavior(QObject* parent, const BehaviorInformation* conf);

        virtual void setActivitySpeedRatio(qreal ratio, const CycleDate& currentDate) override;

        virtual bool acceptItem(const ItemInformation* itemType) const override;

        virtual void process(const CycleDate& date) override;

        virtual bool processInteraction(const CycleDate& date, Character* actor) override;

    signals:
        void hasProduced(const int quantity);
};

#endif // FARMBEHAVIOR_HPP
