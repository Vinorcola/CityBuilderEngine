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
        QList<RandomWalker*> walkers;// TODO: use QWeakPointer.

    public:
        MaintenanceBuilding(Map& map, const MapArea& area, const MapCoordinates& entryPoint);

        virtual void init(const CycleDate& date);

        virtual void process(const CycleDate& date);
};

#endif // MAINTENANCEBUILDING_HPP
