#ifndef HOUSINGBUILDING_HPP
#define HOUSINGBUILDING_HPP

#include "engine/element/dynamic/TargetedWalker.hpp"
#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"

/**
 * @brief A housing building.
 *
 * A housing building receive some inhabitants and consume some items. The housing building is also the only type of
 * building that can evolve into different stages.
 */
class HousingBuilding : public AbstractProcessableStaticMapElement
{
        Q_OBJECT

    private:
        int housingCapacity;
        int inhabitants;
        QPointer<TargetedWalker> currentImmigrant;

    public:
        HousingBuilding(QObject* parent, const StaticElementInformation* conf, const MapArea& area, const MapCoordinates& entryPoint);

        virtual void init(const CycleDate& date);

        virtual void process(const CycleDate& date);

        virtual bool processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor);

    signals:
        void freeCapacityChanged(const int previousFreeCapacity, const int newFreeCapacity, std::function<void(TargetedWalker*)> onImmigrantCreation);

        void inhabitantsChanged(const int inhabitantsDelta);
};

#endif // HOUSINGBUILDING_HPP
