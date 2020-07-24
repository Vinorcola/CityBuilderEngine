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
 * @brief Handle the motion of characters on the map.
 *
 * There are two kind of walking strategy: wanding & targeted.
 *
 * The targeted strategy consist on joining a specific location on the map as fast as possible. It will use A* algorithm
 * to find the shortest path between initial location & targeted location. Once the path is set, it will handle the
 * motion through the `move()` method.
 *
 * The wanderin strategy consist on wandering around, following the roads. The wandering strategy is configurer by
 * giving a `wanderingCredit`. The motion wil start by following the road in a random direction and at each bifurcation,
 * it will choose a random direction. It will keep this motion strategy until the wandering credits are used (one credit
 * allow the character to move through a road node). Once all the wandering credits are used, it will emit
 * `wanderingCreditsExpired()` signal.
 */
class MotionHandler: public QObject
{
        Q_OBJECT

    private:
        const Map* map;
        qreal speed;
        bool restrictedToRoads;
        bool isWanderingStrategy;
        int wanderingCredits;
        MapCoordinates location;///< The current coordinates of the element.
        MapCoordinates movingFrom;///< The coordinates of the tile the element is moving from.
        MapCoordinates movingTo;///< The coordinates of the tile the element is moving to.
        const RoadGraphNode* targetRoadNode;///< The target road node (or nullptr if target is not on roads).
        MapCoordinates target;///< The coordinates of the target.
        QList<const RoadGraphNode*> roadPath;///< The current path to follow.

    public:
        /**
         * @brief Construct a new motion handler.
         *
         * @param map                  The map.
         * @param speed                The speed of the character.
         * @param initialLocation      The initial location of the character.
         * @param randomWalkingCredits The wandering credits.
         * @param restrictedToRoads    Indicates if the motion is restricted to roads.
         */
        MotionHandler(
            QObject* parent,
            const Map* map,
            qreal speed,
            const MapCoordinates& initialLocation,
            int wanderingCredits = 0,
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

        /**
         * @brief Reset the target information.
         *
         * The motion will stop at the current location unless another target is set.
         */
        void resetTarget();

        /**
         * @brief Indicate if the motion as reached the target.
         */
        bool hasReachedTarget() const;

        const MapCoordinates& getCurrentLocation() const;

        MapCoordinates getCurrentTileCoordinates() const;

        /**
         * @brief Move and return the new location.
         */
        const MapCoordinates& move();

    signals:
        /**
         * @brief Emited when the wandering motion has used all the credits.
         */
        void wanderingCreditsExpired();

    private:
        /**
         * @brief Resolve the road node linked to the current location.
         */
        const RoadGraphNode* getCurrentRoadNode() const;

        /**
         * @brief Reset the road path to follow. Must be called each time the target change or that the path is broken.
         */
        void calculatePath();

        /**
         * @brief Resolve the next tile to move to.
         */
        MapCoordinates getNextPathTile();

        /**
         * @brief Select the next tile to wander to.
         */
        MapCoordinates getNextRandomTile();

        /**
         * @brief Execute the motion.
         */
        void moveToTarget();
};

#endif // MOTIONHANDLER_HPP
