#ifndef CITYENTRYPOINT_HPP
#define CITYENTRYPOINT_HPP

#include <functional>
#include <QtCore/QList>

#include "engine/element/static/Building.hpp"

class AbstractDynamicMapElement;
class BehaviorFactory;
class DynamicElementInformation;
class MapCoordinates;
class QueuedWalkerGenerator;
class TargetedWalker;

class CityEntryPoint : public Building
{
        Q_OBJECT

    private:
        QueuedWalkerGenerator* immigrantGenerator;

    public:
        CityEntryPoint(
            QObject* parent,
            const BehaviorFactory* behaviorFactory,
            const StaticElementInformation* conf,
            const MapCoordinates& coordinates
        );

        void requestImmigrant(std::function<void(AbstractDynamicMapElement*)> onWalkerCreation);
};

#endif // CITYENTRYPOINT_HPP
