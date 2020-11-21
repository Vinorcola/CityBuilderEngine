#ifndef DYNAMICELEMENTHANDLER_HPP
#define DYNAMICELEMENTHANDLER_HPP

#include <QtCore/QHash>

#include "src/engine/element/dynamic/CharacterFactoryInterface.hpp"
#include "src/engine/element/dynamic/CharacterManagerInterface.hpp"
#include "src/engine/state/CharacterState.hpp"

class BuildingSearchEngine;
class Character;
class PathGeneratorInterface;

class DynamicElementHandler : public CharacterFactoryInterface, public CharacterManagerInterface
{
    private:
        struct State {
            QHash<Character*, QSharedPointer<Character>> characters;
        };

    private:
        const PathGeneratorInterface& pathGenerator;
        const BuildingSearchEngine& buildingSearchEngine;
        State currentState;

    public:
        DynamicElementHandler(
            const PathGeneratorInterface& pathGenerator,
            const BuildingSearchEngine& buildingSearchEngine
        );

        virtual QWeakPointer<Character> generateDeliveryMan(
            const CharacterInformation& conf,
            QSharedPointer<AbstractProcessableBuilding> issuer,
            const ItemInformation& transportedItemConf,
            const int transportedQuantity = 0
        ) override;
        virtual QWeakPointer<Character> generateImmigrant(
            const CharacterInformation& conf,
            QSharedPointer<AbstractProcessableBuilding> issuer,
            QSharedPointer<AbstractProcessableBuilding> target
        ) override;
        virtual QWeakPointer<Character> generateMiner(
            const CharacterInformation& conf,
            QSharedPointer<AbstractProcessableBuilding> issuer,
            owner<PathInterface*> path
        ) override;
        virtual QWeakPointer<Character> generateStudent(
            const CharacterInformation& conf,
            QSharedPointer<AbstractProcessableBuilding> issuer,
            QSharedPointer<AbstractProcessableBuilding> target
        ) override;
        virtual QWeakPointer<Character> generateWanderingCharacter(
            const CharacterInformation& conf,
            QSharedPointer<AbstractProcessableBuilding> issuer
        ) override;

        virtual void clearCharacter(Character& character) override;

        QList<CharacterState> getCharactersState() const;
};

#endif // DYNAMICELEMENTHANDLER_HPP
