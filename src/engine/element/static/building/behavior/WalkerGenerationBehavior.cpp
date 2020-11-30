#include "WalkerGenerationBehavior.hpp"

#include <QtCore/QtAlgorithms>

#include "src/defines.hpp"



WalkerGenerationBehavior::WalkerGenerationBehavior(int maxWorkers, int generationInterval) :
    GENERATION_INTERVAL(generationInterval * maxWorkers),
    POSTPONE_INTERVAL(qMin(generationInterval, 2 * BUILDING_CYCLES_PER_SECOND) * maxWorkers),
    generationCountDown(GENERATION_INTERVAL)
{

}



bool WalkerGenerationBehavior::isReadyToGenerateWalker() const
{
    return generationCountDown <= 0;
}



void WalkerGenerationBehavior::process(int currentWorkers)
{
    if (generationCountDown > 0) {
        generationCountDown -= currentWorkers;
    }
}



void WalkerGenerationBehavior::postpone()
{
    if (generationCountDown < POSTPONE_INTERVAL) {
        generationCountDown = POSTPONE_INTERVAL;
    }
}



void WalkerGenerationBehavior::reset()
{
    generationCountDown = GENERATION_INTERVAL;
}
