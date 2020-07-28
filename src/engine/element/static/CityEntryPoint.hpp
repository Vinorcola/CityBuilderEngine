#ifndef CITYENTRYPOINT_HPP
#define CITYENTRYPOINT_HPP

#include <functional>
#include <QtCore/QList>
#include <QtCore/QObject>

#include "src/engine/element/static/ProcessableBuilding.hpp"

class Character;
class CycleDate;
class BehaviorFactory;
class MapCoordinates;
class QueuedWalkerGenerator;

/**
 * @brief A specific building that represent the map entry point.
 *
 * The entry point has the specificity of generating incomming walkers from outside the city. For the moment, it can
 * only generates immigrants. It does not generate immigrants as soon as requested. Instead, it spread the generation
 * over time.
 */
class CityEntryPoint : public ProcessableBuilding
{
        Q_OBJECT

    private:
        QueuedWalkerGenerator* immigrantGenerator;

    public:
        CityEntryPoint(
            QObject* parent,
            const BuildingInformation* conf,
            const MapCoordinates& coordinates
        );

        void requestImmigrant(std::function<void(Character*)> onWalkerCreation);

        virtual void process(const CycleDate& date);
};

#endif // CITYENTRYPOINT_HPP
