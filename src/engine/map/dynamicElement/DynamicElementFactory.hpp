#ifndef DYNAMICELEMENTFACTORY_HPP
#define DYNAMICELEMENTFACTORY_HPP

#include <QtCore/QSharedPointer>

class AbstractProcessableBuilding;
class BuildingSearchEngine;
class Character;
class CharacterDisposerInterface;
class CharacterInformation;
class ItemInformation;
class NatureElementSearchEngine;
class PathGeneratorInterface;
class PathInterface;

class DynamicElementFactory
{
        Q_DISABLE_COPY_MOVE(DynamicElementFactory)

    public:
        DynamicElementFactory(
            CharacterDisposerInterface& characterDisposer,
            const PathGeneratorInterface& pathGenerator,
            const BuildingSearchEngine& buildingSearchEngine,
            const NatureElementSearchEngine& natureElementSearchEngine
        );

        QSharedPointer<Character> generateDeliveryMan(
            const CharacterInformation& conf,
            QSharedPointer<AbstractProcessableBuilding> issuer,
            const ItemInformation& transportedItemConf,
            const int transportedQuantity = 0
        );

        QSharedPointer<Character> generateImmigrant(
            const CharacterInformation& conf,
            QSharedPointer<AbstractProcessableBuilding> issuer,
            QSharedPointer<AbstractProcessableBuilding> target
        );

        QSharedPointer<Character> generateMiner(
            const CharacterInformation& conf,
            QSharedPointer<AbstractProcessableBuilding> issuer,
            QSharedPointer<PathInterface> path
        );

        QSharedPointer<Character> generateStudent(
            const CharacterInformation& conf,
            QSharedPointer<AbstractProcessableBuilding> issuer,
            QSharedPointer<AbstractProcessableBuilding> target
        );

        QSharedPointer<Character> generateWanderingCharacter(
            const CharacterInformation& conf,
            QSharedPointer<AbstractProcessableBuilding> issuer
        );

    private:
        CharacterDisposerInterface& characterDisposer;
        const PathGeneratorInterface& pathGenerator;
        const BuildingSearchEngine& buildingSearchEngine;
        const NatureElementSearchEngine& natureElementSearchEngine;
};

#endif // DYNAMICELEMENTFACTORY_HPP
