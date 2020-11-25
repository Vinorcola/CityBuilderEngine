#include "WalkerGenerationBehavior.hpp"

#include <QtCore/QtAlgorithms>

#include "src/defines.hpp"



WalkerGenerationBehavior::WalkerGenerationBehavior(int maxWorkers, int generationInterval) :
    MAX_WORKERS(maxWorkers),
    GENERATION_INTERVAL(generationInterval * maxWorkers),
    POSTPONE_INTERVAL(qMin(generationInterval, 2 * CYCLE_PER_SECOND) * maxWorkers),
    generationCountDown(0)
{
    reset();
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
    generationCountDown = GENERATION_INTERVAL * MAX_WORKERS;
}
