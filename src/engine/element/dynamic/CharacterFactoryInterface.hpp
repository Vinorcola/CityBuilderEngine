#ifndef CHARACTERFACTORYINTERFACE_HPP
#define CHARACTERFACTORYINTERFACE_HPP

#include "src/defines.hpp"

class Character;
class CharacterInformation;
class DeliveryManCharacter;
class ItemInformation;
class MinerCharacter;
class NatureElement;
class PathInterface;
class ProcessableBuilding;
class WanderingCharacter;

class CharacterFactoryInterface
{
    public:
        virtual ~CharacterFactoryInterface();

        virtual MinerCharacter& generateMiner(
            const CharacterInformation& conf,
            ProcessableBuilding& issuer,
            owner<PathInterface*> path
        ) = 0;

        virtual DeliveryManCharacter& generateDeliveryMan(
            const CharacterInformation& conf,
            ProcessableBuilding& issuer,
            const ItemInformation& transportedItemConf,
            const int transportedQuantity = 0
        ) = 0;

        virtual WanderingCharacter& generateWanderingCharacter(
            const CharacterInformation& conf,
            ProcessableBuilding& issuer
        ) = 0;

        virtual void clearCharacter(Character& character) = 0;
};

#endif // CHARACTERFACTORYINTERFACE_HPP
