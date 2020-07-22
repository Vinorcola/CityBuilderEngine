#ifndef RANDOMWALKER_HPP
#define RANDOMWALKER_HPP

#include "engine/element/dynamic/TargetedWalker.hpp"
#include "engine/map/MapCoordinates.hpp"

class AbstractProcessableStaticMapElement;
class CycleDate;
class DynamicElementInformation;
class RoadGraph;

/**
 * @brief A random walker walks on the roads and take random directions at road intersections.
 *
 * The random walker does have a walking credit. Each tile walked on consumes one credit. As soon as the walking credit
 * has expired, the random walker become a targeted walker.
 */
class RandomWalker : public TargetedWalker
{
        Q_OBJECT

    private:
        int walkingCredit;

    public:
        RandomWalker(
            QObject* parent,
            const DynamicElementInformation* conf,
            const RoadGraph& roadGraph,
            AbstractProcessableStaticMapElement* issuer
        );

        virtual void assignTarget(AbstractProcessableStaticMapElement* targetElement) override;

    protected:
        virtual MapCoordinates findNextGoingToLocation(const CycleDate& date) override;
};

#endif // RANDOMWALKER_HPP
