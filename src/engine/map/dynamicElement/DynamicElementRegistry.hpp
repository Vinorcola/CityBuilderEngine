#ifndef DYNAMICELEMENTREGISTRY_HPP
#define DYNAMICELEMENTREGISTRY_HPP

#include <QtCore/QHash>
#include <QtCore/QList>
#include <QtCore/QSharedPointer>

#include "src/engine/map/dynamicElement/CharacterDisposerInterface.hpp"
#include "src/engine/map/dynamicElement/CharacterGeneratorInterface.hpp"
#include "src/engine/map/dynamicElement/DynamicElementFactory.hpp"
#include "src/engine/processing/AbstractProcessable.hpp"
#include "src/global/state/CharacterState.hpp"

class Character;

class DynamicElementRegistry : public AbstractProcessable, public CharacterDisposerInterface, public CharacterGeneratorInterface
{
        Q_DISABLE_COPY_MOVE(DynamicElementRegistry)

    public:
        explicit DynamicElementRegistry(
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
            QSharedPointer<PathInterface> path
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

        // State.
        QList<CharacterState> getCharactersState() const;

        virtual void process(const CycleDate& date) override;

    private:
        DynamicElementFactory factory;
        QHash<const Character*, QSharedPointer<Character>> characters;
        QList<QSharedPointer<Character>> waitingForRegistrationList;
        QList<const Character*> waitingForUnregistrationList;
};

#endif // DYNAMICELEMENTREGISTRY_HPP
