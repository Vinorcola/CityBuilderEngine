#ifndef TARGETEDWALKER_HPP
#define TARGETEDWALKER_HPP

#include "engine/element/character/AbstractCharacter.hpp"
#include "engine/map/roadGraph/RoadGraphNode.hpp"

/**
 * @brief A targeted walker walks on the roads toward a specific target.
 *
 * Note that target is not assigned at the walker creation because some walker may simply not have any target after
 * being created. In this case, the walker is not moving and stays where it is. As soon as the target is assigned, the
 * walker will begin ihis journey toward the target.
 */
class TargetedWalker : public AbstractCharacter
{
    private:
        MapCoordinates targetLocation;
        QList<const RoadGraphNode*> path;
        bool hasTargetBeenAssigned;

    protected:
        const RoadGraph& roadGraph;

    public:
        TargetedWalker(const RoadGraph& roadGraph, const MapCoordinates& initialPosition);

        void assignTarget(const MapCoordinates& target);

        bool hasTarget() const;

        bool hasReachableTarget() const;

        bool reachedTarget() const;

    protected:
        virtual MapCoordinates findNextGoingToLocation();
};

#endif // TARGETEDWALKER_HPP
