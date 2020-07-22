#ifndef INHABITANTCONTAINER_HPP
#define INHABITANTCONTAINER_HPP

#include <functional>
#include <QtCore/QPointer>

#include "engine/element/dynamic/TargetedWalker.hpp"
#include "engine/element/static/behavior/AbstractStaticElementBehavior.hpp"

class AbstractProcessableStaticMapElement;

/**
 * @brief An inhabitant holder.
 *
 * A behavior that allow the building to holds some inhabitants.
 */
class InhabitantContainer : public AbstractStaticElementBehavior
{
        Q_OBJECT

    private:
        AbstractProcessableStaticMapElement* issuer;
        int housingCapacity;
        int inhabitants;
        QPointer<TargetedWalker> currentImmigrant;

    public:
        InhabitantContainer(AbstractProcessableStaticMapElement* issuer);

        virtual void init(const CycleDate& date) override;

        virtual void process(const CycleDate& date) override;

        virtual bool processInteraction(const CycleDate& date, Character* actor) override;

    signals:
        void freeCapacityChanged(
            const int previousFreeCapacity,
            const int newFreeCapacity,
            std::function<void(Character*)> onImmigrantCreation
        );

        void inhabitantsChanged(const int inhabitantsDelta);

        void requestDynamicElementDestruction(
            Character* element,
            std::function<void()> afterDestruction
        );
};

#endif // INHABITANTCONTAINER_HPP
