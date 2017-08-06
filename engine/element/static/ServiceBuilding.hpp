#ifndef SERVICEBUILDING_HPP
#define SERVICEBUILDING_HPP

#include "engine/element/dynamic/RandomWalker.hpp"
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
        CycleDate nextWalkerGenerationDate;
        QList<QPointer<RandomWalker>> walkers;

    public:
        ServiceBuilding(QObject* parent, const StaticElementInformation* conf, const MapArea& area, const MapCoordinates& entryPoint);

        virtual void init(const CycleDate& date);

        virtual void process(const CycleDate& date);

        virtual void processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor);

    protected:
        void setupNextWalkerGenerationDate(const CycleDate& currentDate);
};

#endif // SERVICEBUILDING_HPP
