#ifndef HOUSINGBUILDING_HPP
#define HOUSINGBUILDING_HPP

#include "engine/element/dynamic/TargetedWalker.hpp"
#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"

class HousingBuilding : public AbstractProcessableStaticMapElement
{
        Q_OBJECT

    private:
        int housingCapacity;
        int inhabitants;
        QPointer<TargetedWalker> currentImmigrant;

    public:
        HousingBuilding(QObject* parent, const MapArea& area, const MapCoordinates& entryPoint);

        virtual void init(const CycleDate& date);

        virtual void process(const CycleDate& date);

        virtual void processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor);

    signals:
        void freeCapacityChanged(const int previousFreeCapacity, const int newFreeCapacity, std::function<void(TargetedWalker*)> onImmigrantCreation);

        void inhabitantsChanged(const int inhabitantsDelta);
};

#endif // HOUSINGBUILDING_HPP
