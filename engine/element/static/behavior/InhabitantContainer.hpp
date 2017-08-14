#ifndef INHABITANTCONTAINER_HPP
#define INHABITANTCONTAINER_HPP

#include <functional>
#include <QtCore/QPointer>

#include "engine/element/dynamic/TargetedWalker.hpp"
#include "engine/element/static/behavior/AbstractStaticElementBehavior.hpp"

class AbstractProcessableStaticMapElement;

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

        virtual bool processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor) override;

        virtual void setActivitySpeedRatio(qreal ratio, const CycleDate& currentDate) override;

    signals:
        void freeCapacityChanged(
            const int previousFreeCapacity,
            const int newFreeCapacity,
            AbstractProcessableStaticMapElement* issuer,
            std::function<void(TargetedWalker*)> onImmigrantCreation
        );

        void inhabitantsChanged(const int inhabitantsDelta);

        void requestDynamicElementDestruction(
            AbstractDynamicMapElement* element,
            std::function<void()> afterDestruction
        );
};

#endif // INHABITANTCONTAINER_HPP
