#ifndef SERVICEBUILDING_HPP
#define SERVICEBUILDING_HPP

#include "engine/element/WalkerPool.hpp"
#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"

/**
 * @brief A service building.
 *
 * Service buildings mainly provide with random walkers that provide a service while they are walking through the map.
 */
class ServiceBuilding : public AbstractProcessableStaticMapElement
{
        Q_OBJECT

    private:
        WalkerPool* randomWalkers;
        CycleDate canGenerateWalkersUntil;

    public:
        ServiceBuilding(QObject* parent, const StaticElementInformation* conf, const MapArea& area, const MapCoordinates& entryPoint);

        virtual void init(const CycleDate& date);

        virtual void process(const CycleDate& date);

        virtual bool processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor);
};

#endif // SERVICEBUILDING_HPP
