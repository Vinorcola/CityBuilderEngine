#include "RandomWalkerGenerator.hpp"



RandomWalkerGenerator::RandomWalkerGenerator(
    ProcessableBuilding* issuer,
    const CharacterInformation& walkerConf,
    const int generationInterval,
    const int maxWalkers
) :
    AbstractWalkerGenerator(issuer, walkerConf, generationInterval, maxWalkers)
{

}
