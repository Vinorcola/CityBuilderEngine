#ifndef BUILDINGWITHBEHAVIOR_HPP
#define BUILDINGWITHBEHAVIOR_HPP

#include <functional>
#include <QtCore/QList>
#include <QtCore/QObject>

#include "src/engine/element/static/ProcessableBuilding.hpp"
#include "src/engine/processing/AbstractProcessable.hpp"

class AbstractBehavior;
class BehaviorFactory;
class BuildingInformation;
class Character;
class CharacterInformation;
class CycleDate;
class ItemInformation;
class MapArea;
class MapCoordinates;

/**
 * @brief A processable building.
 *
 * A processable building is a building that can be processed by the time-cycle processor. In order to be processed, it
 * will hold some behaviors. Each behavior will be processed and will fullfill a specific purpose. Behaviors are
 * instanciated using the given building configuration.
 */
class BuildingWithBehaviors : public ProcessableBuilding
{
        Q_OBJECT

    private:
        QList<AbstractBehavior*> behaviors;

    public:
        BuildingWithBehaviors(
            QObject* parent,
            const BehaviorFactory* behaviorFactory,
            const BuildingInformation& conf,
            const MapArea& area,
            const MapCoordinates& entryPoint
        );

        virtual void init(const CycleDate& date) override;

        virtual void process(const CycleDate& date) override;

        /**
         * @brief Process an interaction with a character and the building.
         *
         * @param actor The actor of the interaction.
         * @return Indicate if the actor was processed or not.
         */
        bool processInteraction(const CycleDate& date, Character* actor);

        void notifyWalkerDestruction();

        bool acceptItem(const ItemInformation& itemType) const;

    signals:
        void requestCharacterCreation(
            const CharacterInformation& conf,
            std::function<void(Character*)> afterCreation
        );

        void requestCharacterDestruction(
            Character* character,
            std::function<void()> afterDestruction
        );

    protected:
        const QList<AbstractBehavior*>& getBehaviors() const;
};

#endif // BUILDINGWITHBEHAVIOR_HPP
