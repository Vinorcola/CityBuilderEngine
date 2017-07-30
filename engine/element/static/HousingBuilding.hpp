#ifndef HOUSINGBUILDING_HPP
#define HOUSINGBUILDING_HPP

#include <QWeakPointer>

#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"
#include "engine/element/static/CityEntryPoint.hpp"
#include "engine/map/CityStatus.hpp"

class Map;

class HousingBuilding : public AbstractProcessableStaticMapElement
{
    private:
        Map& map;
        CityStatus& cityStatus;
        QWeakPointer<CityEntryPoint> cityEntryPoint;
        int housingCapacity;
        int population;

    public:
        HousingBuilding(Map& map, const MapArea& area, const MapCoordinates& entryPoint, CityStatus& cityStatus, QWeakPointer<CityEntryPoint> cityEntryPoint);

        virtual void process(const CycleDate& date);

        virtual void processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor);
};

#endif // HOUSINGBUILDING_HPP
