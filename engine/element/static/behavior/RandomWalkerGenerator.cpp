#include "RandomWalkerGenerator.hpp"



RandomWalkerGenerator::RandomWalkerGenerator(
    AbstractProcessableStaticMapElement* issuer,
    const CharacterInformation* walkerConf,
    const int generationInterval,
    const int maxWalkers
) :
    AbstractWalkerGenerator(issuer, walkerConf, generationInterval, maxWalkers)
{

}
