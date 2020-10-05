#ifndef CHARACTERFACTORYINTERFACE_HPP
#define CHARACTERFACTORYINTERFACE_HPP

#include "src/defines.hpp"

class Character;
class CharacterInformation;
class DeliveryManCharacter;
class ImmigrantCharacter;
class ItemInformation;
class MinerCharacter;
class NatureElement;
class PathInterface;
class ProcessableBuilding;
class StudentCharacter;
class WanderingCharacter;

class CharacterFactoryInterface
{
    public:
        virtual ~CharacterFactoryInterface();

        virtual DeliveryManCharacter& generateDeliveryMan(
            const CharacterInformation& conf,
            ProcessableBuilding& issuer,
            const ItemInformation& transportedItemConf,
            const int transportedQuantity = 0
        ) = 0;

        virtual ImmigrantCharacter& generateImmigrant(const CharacterInformation& conf) = 0;

        virtual MinerCharacter& generateMiner(
            const CharacterInformation& conf,
            ProcessableBuilding& issuer,
            owner<PathInterface*> path
        ) = 0;

        virtual StudentCharacter& generateStudent(
            const CharacterInformation& conf,
            ProcessableBuilding& issuer,
            ProcessableBuilding& target
        ) = 0;

        virtual WanderingCharacter& generateWanderingCharacter(
            const CharacterInformation& conf,
            ProcessableBuilding& issuer
        ) = 0;

        virtual void clearCharacter(Character& character) = 0;
};

#endif // CHARACTERFACTORYINTERFACE_HPP
