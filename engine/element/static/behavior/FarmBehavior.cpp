#include "FarmBehavior.hpp"

#include <assert.h>

#include "global/conf/BehaviorInformation.hpp"

const int MAX_QUANTITY(8);



FarmBehavior::FarmBehavior(QObject* parent, const BehaviorInformation* conf) :
    AbstractActivityBehavior(parent),
    conf(conf),
    completeGrowingDate(),
    remainingGrowthInterval(CycleDate::getCyclesPerYear())
{

}



void FarmBehavior::setActivitySpeedRatio(qreal ratio, const CycleDate& currentDate)
{
    assert(ratio >= 0.0);
    assert(ratio <= 1.0);

    // If ratio does not change, we avoid useless calculations.
    if (activitySpeedRatio == ratio) {
        return;
    }

    if (ratio == 0.0) {
        remainingGrowthInterval = activitySpeedRatio * (completeGrowingDate - currentDate);
        activitySpeedRatio = 0.0;
        completeGrowingDate.reset();
    } else {
        // Calculate the next generation date and setup ratio.
        if (activitySpeedRatio == 0.0) {
            completeGrowingDate.reassign(currentDate, remainingGrowthInterval / ratio);
            remainingGrowthInterval = 0;
        } else {
            completeGrowingDate.reassign(currentDate, (completeGrowingDate - currentDate) * ratio / activitySpeedRatio);
        }

        activitySpeedRatio = ratio;
    }
}



bool FarmBehavior::acceptItem(const ItemInformation* /*itemType*/) const
{
    return false;
}



void FarmBehavior::process(const CycleDate& date)
{
    if (date.isFirstCycleOfMonth() && date.getMonth() == conf->getHarvestMonth()) {
        remainingGrowthInterval = activitySpeedRatio * (completeGrowingDate - date);
        if (remainingGrowthInterval < 0) {
            remainingGrowthInterval = 0;
        }
        qreal productivityRatio(CycleDate::getCyclesPerYear() / (CycleDate::getCyclesPerYear() + remainingGrowthInterval));
        int quantity(productivityRatio * MAX_QUANTITY);

        emit hasProduced(quantity);
    }
}



bool FarmBehavior::processInteraction(const CycleDate& /*date*/, Character* /*actor*/)
{
    return false;
}
