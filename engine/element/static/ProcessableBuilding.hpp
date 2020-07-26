#ifndef PROCESSABLEBUILDING_HPP
#define PROCESSABLEBUILDING_HPP

#include <functional>
#include <QtCore/QList>
#include <QtCore/QObject>

#include "engine/element/static/Building.hpp"
#include "engine/map/MapCoordinates.hpp"
#include "engine/processing/AbstractProcessable.hpp"

class AbstractBehavior;
class BehaviorFactory;
class BuildingInformation;
class Character;
class CharacterInformation;
class CycleDate;
class ItemInformation;
class MapArea;

/**
 * @brief A processable building.
 *
 * A processable building is a building that can be processed by the time-cycle processor. In order to be processed, it
 * will hold some behaviors. Each behavior will be processed and will fullfill a specific purpose. Behaviors are
 * instanciated using the given building configuration.
 */
class ProcessableBuilding : public Building, public AbstractProcessable
{
        Q_OBJECT

    private:
        QList<AbstractBehavior*> behaviors;
        MapCoordinates entryPoint;

    public:
        ProcessableBuilding(
            QObject* parent,
            const BehaviorFactory* behaviorFactory,
            const BuildingInformation* conf,
            const MapArea& area,
            const MapCoordinates& entryPoint
        );

        const MapCoordinates& getEntryPoint() const;

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

        bool acceptItem(const ItemInformation* itemType) const;

    signals:
        void requestCharacterCreation(
            const CharacterInformation* conf,
            std::function<void(Character*)> afterCreation
        );

        void requestCharacterDestruction(
            Character* character,
            std::function<void()> afterDestruction
        );

    protected:
        const QList<AbstractBehavior*>& getBehaviors() const;
};

#endif // PROCESSABLEBUILDING_HPP
