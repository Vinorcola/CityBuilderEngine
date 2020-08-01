#ifndef CHARACTERFACTORYINTERFACE_HPP
#define CHARACTERFACTORYINTERFACE_HPP

#include "src/defines.hpp"

class Character;
class CharacterInformation;
class MinerCharacter;
class NatureElement;
class PathInterface;
class ProcessableBuilding;

class CharacterFactoryInterface
{
    public:
        virtual ~CharacterFactoryInterface();

        virtual MinerCharacter& generateMiner(
            const CharacterInformation& conf,
            ProcessableBuilding& issuer,
            owner<PathInterface*> path
        ) = 0;

        virtual void clearCharacter(Character& character) = 0;
};

#endif // CHARACTERFACTORYINTERFACE_HPP
