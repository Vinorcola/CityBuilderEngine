#ifndef CITYENTRYPOINT_HPP
#define CITYENTRYPOINT_HPP

#include "engine/element/building/AbstractProcessableBuilding.hpp"

class CityEntryPoint : public AbstractProcessableBuilding
{
    public:
        CityEntryPoint(const MapCoordinates& coordinates);

        virtual void process(const CycleDate& date);

        virtual void processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor);
};

#endif // CITYENTRYPOINT_HPP
