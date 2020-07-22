#ifndef CITYENTRYPOINT_HPP
#define CITYENTRYPOINT_HPP

#include <functional>
#include <QtCore/QList>

#include "engine/element/static/Building.hpp"

class Character;
class BehaviorFactory;
class DynamicElementInformation;
class MapCoordinates;
class QueuedWalkerGenerator;
class TargetedWalker;

/**
 * @brief A specific building that represent an entry point of the city.
 *
 * The city entry point has the specificity of generating incomming walkers from outside the city. For the moment, it
 * can only generates immigrants. It does not generate an mmigrant as soon as requested. Instead, it spread the
 * generation over time.
 */
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

        void requestImmigrant(std::function<void(Character*)> onWalkerCreation);
};

#endif // CITYENTRYPOINT_HPP
