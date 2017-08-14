#ifndef CITYENTRYPOINT_HPP
#define CITYENTRYPOINT_HPP

#include <functional>
#include <QtCore/QList>

#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"
#include "engine/processing/CycleDate.hpp"

class AbstractDynamicMapElement;
class DynamicElementInformation;
class MapCoordinates;
class TargetedWalker;

class CityEntryPoint : public AbstractProcessableStaticMapElement
{
        Q_OBJECT

    private:
        const DynamicElementInformation* immigrantConf;
        CycleDate nextImmigrantGenerationDate;
        QList<std::function<void(AbstractDynamicMapElement*)>> immigrantRequestQueue;

    public:
        CityEntryPoint(
            QObject* parent,
            const StaticElementInformation* conf,
            const MapCoordinates& coordinates,
            const DynamicElementInformation* immigrantConf
        );

        virtual void process(const CycleDate& date);

        virtual bool processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor);

    public slots:
        void registerImmigrantRequest(AbstractProcessableStaticMapElement* issuer, std::function<void(TargetedWalker*)> onImmigrantCreation);

    protected:
        void setupNextImmigrantGenerationDate(const CycleDate& currentDate);
};

#endif // CITYENTRYPOINT_HPP
