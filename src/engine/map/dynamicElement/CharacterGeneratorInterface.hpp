#ifndef CHARACTERGENERATORINTERFACE_HPP
#define CHARACTERGENERATORINTERFACE_HPP

#include <QtCore/QWeakPointer>

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

class CharacterGeneratorInterface
{
    public:
        virtual ~CharacterGeneratorInterface() {};

        virtual QWeakPointer<Character> generateDeliveryMan(
            const CharacterInformation& conf,
            QSharedPointer<AbstractProcessableBuilding> issuer,
            const ItemInformation& transportedItemConf,
            const int transportedQuantity = 0
        ) = 0;

        virtual QWeakPointer<Character> generateImmigrant(
            const CharacterInformation& conf,
            QSharedPointer<AbstractProcessableBuilding> issuer,
            QSharedPointer<AbstractProcessableBuilding> target
        ) = 0;

        virtual QWeakPointer<Character> generateMiner(
            const CharacterInformation& conf,
            QSharedPointer<AbstractProcessableBuilding> issuer,
            owner<PathInterface*> path
        ) = 0;

        virtual QWeakPointer<Character> generateStudent(
            const CharacterInformation& conf,
            QSharedPointer<AbstractProcessableBuilding> issuer,
            QSharedPointer<AbstractProcessableBuilding> target
        ) = 0;

        virtual QWeakPointer<Character> generateWanderingCharacter(
            const CharacterInformation& conf,
            QSharedPointer<AbstractProcessableBuilding> issuer
        ) = 0;
};

#endif // CHARACTERGENERATORINTERFACE_HPP
