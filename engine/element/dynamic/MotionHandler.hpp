#ifndef MOTIONHANDLER_HPP
#define MOTIONHANDLER_HPP

#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QPointer>

#include "engine/map/MapCoordinates.hpp"

class Character;
class Map;
class RoadGraphNode;

/**
 * @brief Motion information and logic.
 */
class MotionHandler: public QObject
{
        Q_OBJECT

    private:
        const Map* map;
        qreal speed;
        bool restrictedToRoads;
        bool randomWalker;
        int randomWalkingCredit;
        MapCoordinates location;///< The current coordinates of the element.
        MapCoordinates moveFrom;///< The coordinates of the tile the element is moving from.
        MapCoordinates moveTo;///< The coordinates of the tile the element is moving to.
        const RoadGraphNode* targetRoadNode;///< The target road node (or nullptr if target is not on roads).
        MapCoordinates target;///< The coordinates of the target.
        QList<const RoadGraphNode*> roadPath;///< The current path to follow.

    public:
        /**
         * @brief Construct a new motion handler.
         *
         * @param map                 The map.
         * @param speed               The speed of the element.
         * @param randomWalkingCredit The quantity of road nodes the walker can wander around.
         * @param restrictedToRoads   Indicates if the motion is restricted to roads.
         */
        MotionHandler(
            QObject* parent,
            const Map* map,
            qreal speed,
            const MapCoordinates& initialLocation,
            int randomWalkingCredit = 0,
            bool restrictedToRoads = true
        );

        /**
         * @brief Set a road target.
         */
        void setTarget(const RoadGraphNode* location);

        /**
         * @brief Set a target.
         *
         * Prefer setTarget() with a road node if available.
         */
        void setTarget(const MapCoordinates& location);

        void resetTarget();

        bool hasReachedTarget() const;

        const MapCoordinates& getCurrentLocation() const;

        MapCoordinates getCurrentTileCoordinates() const;

        /**
         * @brief Move and return the new location's coordinates.
         */
        const MapCoordinates& move();

    signals:
        void walkingCreditExpired();

    private:
        const RoadGraphNode* getCurrentRoadNode() const;

        void calculatePath();

        MapCoordinates getNextPathTile();

        MapCoordinates getNextRandomTile();

        void moveToTarget();
};

#endif // MOTIONHANDLER_HPP
