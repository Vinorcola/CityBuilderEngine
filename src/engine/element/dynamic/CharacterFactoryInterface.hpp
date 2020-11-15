#ifndef CHARACTERFACTORYINTERFACE_HPP
#define CHARACTERFACTORYINTERFACE_HPP

#include "src/defines.hpp"

class Character;
class CharacterInformation;
class DeliveryManCharacter;
class ImmigrantCharacter;
class ItemInformation;
class MapCoordinates;
class MinerCharacter;
class NatureElement;
class PathInterface;
class AbstractProcessableBuilding;
class StudentCharacter;
class WanderingCharacter;

class CharacterFactoryInterface
{
    public:
        virtual ~CharacterFactoryInterface() {};

        virtual DeliveryManCharacter& generateDeliveryMan(
            const CharacterInformation& conf,
            AbstractProcessableBuilding& issuer,
            const ItemInformation& transportedItemConf,
            const int transportedQuantity = 0
        ) = 0;

        virtual ImmigrantCharacter& generateImmigrant(
            const CharacterInformation& conf,
            AbstractProcessableBuilding& issuer,
            AbstractProcessableBuilding& target
        ) = 0;

        virtual MinerCharacter& generateMiner(
            const CharacterInformation& conf,
            AbstractProcessableBuilding& issuer,
            owner<PathInterface*> path
        ) = 0;

        virtual StudentCharacter& generateStudent(
            const CharacterInformation& conf,
            AbstractProcessableBuilding& issuer,
            AbstractProcessableBuilding& target
        ) = 0;

        virtual WanderingCharacter& generateWanderingCharacter(
            const CharacterInformation& conf,
            AbstractProcessableBuilding& issuer
        ) = 0;
};

#endif // CHARACTERFACTORYINTERFACE_HPP
