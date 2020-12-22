#ifndef CHARACTERGENERATORINTERFACE_HPP
#define CHARACTERGENERATORINTERFACE_HPP

#include <QtCore/QSharedPointer>
#include <QtCore/QWeakPointer>

class Character;
class CharacterInformation;
class ItemInformation;
class PathInterface;
class AbstractProcessableBuilding;

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
            QSharedPointer<PathInterface> path
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
