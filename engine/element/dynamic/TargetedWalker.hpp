#ifndef TARGETEDWALKER_HPP
#define TARGETEDWALKER_HPP

#include <QtCore/QList>
#include <QtCore/QPointer>

#include "engine/element/dynamic/AbstractDynamicMapElement.hpp"
#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"
#include "engine/map/MapCoordinates.hpp"

class CycleDate;
class DynamicElementInformation;
class RoadGraph;
class RoadGraphNode;

/**
 * @brief A targeted walker walks on the roads toward a specific target.
 *
 * The target is not assigned at the walker creation because some walker may simply not have any target at that moment.
 * In this case, the walker is simply not moving and stays where it is. As soon as the target is assigned, the walker
 * will begin its journey toward the target following the calculated path.
 */
class TargetedWalker : public AbstractDynamicMapElement
{
        Q_OBJECT

    private:
        QPointer<AbstractProcessableStaticMapElement> targetElement;
        MapCoordinates targetLocation;
        QList<const RoadGraphNode*> path;

    protected:
        const RoadGraph& roadGraph;

    public:
        TargetedWalker(QObject* parent,
            const DynamicElementInformation* conf,
            const RoadGraph& roadGraph,
            AbstractProcessableStaticMapElement* issuer
        );

        virtual void assignTarget(AbstractProcessableStaticMapElement* targetElement);

        bool hasTarget() const;

        bool hasReachableTarget() const;

        bool reachedTarget() const;

    protected:
        virtual MapCoordinates findNextGoingToLocation(const CycleDate& date) override;
};

#endif // TARGETEDWALKER_HPP
