#ifndef HOUSINGBUILDING_HPP
#define HOUSINGBUILDING_HPP

#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"

class HousingBuilding : public AbstractProcessableStaticMapElement
{
        Q_OBJECT

    private:
        int housingCapacity;
        int population;

    public:
        HousingBuilding(QObject* parent, const MapArea& area, const MapCoordinates& entryPoint);

        virtual void process(const CycleDate& date);

        virtual void processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor);
};

#endif // HOUSINGBUILDING_HPP
