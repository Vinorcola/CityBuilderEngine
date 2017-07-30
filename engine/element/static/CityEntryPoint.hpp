#ifndef CITYENTRYPOINT_HPP
#define CITYENTRYPOINT_HPP

#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"

class CityEntryPoint : public AbstractProcessableStaticMapElement
{
        Q_OBJECT

    public:
        CityEntryPoint(QObject* parent, const MapCoordinates& coordinates);

        virtual void process(const CycleDate& date);

        virtual void processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor);
};

#endif // CITYENTRYPOINT_HPP
