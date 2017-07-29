#ifndef MAINTENANCEBUILDING_HPP
#define MAINTENANCEBUILDING_HPP

#include "engine/element/building/AbstractProcessableBuilding.hpp"
#include "engine/element/character/RandomWalker.hpp"

class Map;

/**
 * @brief A maintenance building for testing purpose.
 */
class MaintenanceBuilding : public AbstractProcessableBuilding
{
    private:
        Map& map;
        CycleDate nextWalkerGenerationDate;
        QList<QWeakPointer<RandomWalker>> walkers;// TODO: use QWeakPointer.

    public:
        MaintenanceBuilding(Map& map, const MapArea& area, const MapCoordinates& entryPoint);

        virtual void init(const CycleDate& date);

        virtual void process(const CycleDate& date);

        virtual void processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor);

    protected:
        void setupWalkerGeneration(const CycleDate& currentDate);
};

#endif // MAINTENANCEBUILDING_HPP
