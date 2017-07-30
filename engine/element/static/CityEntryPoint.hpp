#ifndef CITYENTRYPOINT_HPP
#define CITYENTRYPOINT_HPP

#include "engine/element/dynamic/TargetedWalker.hpp"
#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"

class CityEntryPoint : public AbstractProcessableStaticMapElement
{
        Q_OBJECT

    private:
        CycleDate nextImmigrantGenerationDate;
        QList<std::function<void(AbstractDynamicMapElement*)>> immigrantRequestQueue;

    public:
        CityEntryPoint(QObject* parent, const MapCoordinates& coordinates);

        virtual void process(const CycleDate& date);

        virtual void processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor);

    public slots:
        void registerImmigrantRequest(AbstractProcessableStaticMapElement* issuer, std::function<void(TargetedWalker*)> onImmigrantCreation);

    protected:
        void setupNextImmigrantGenerationDate(const CycleDate& currentDate);
};

#endif // CITYENTRYPOINT_HPP
