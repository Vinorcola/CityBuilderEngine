#ifndef MOTIONHANDLER_HPP
#define MOTIONHANDLER_HPP

#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QPointer>

#include "src/engine/map/MapCoordinates.hpp"
#include "src/defines.hpp"

class PathGenerator;
class PathInterface;
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
        const PathGenerator& pathGenerator;
        const qreal speed;
        const bool restrictedToRoads;
        MapCoordinates destination;///< The coordinates of the target.
        owner<PathInterface*> path;///< The path to follow.
        MapCoordinates location;///< The current coordinates of the element.
        MapCoordinates movingFrom;///< The coordinates of the tile the element is moving from.
        MapCoordinates movingTo;///< The coordinates of the tile the element is moving to.

    public:
        /**
         * @brief Construct a new motion handler for a wandering character.
         *
         * @param speed                The speed of the character.
         * @param initialLocation      The initial location of the character.
         * @param randomWalkingCredits The wandering credits.
         */
        MotionHandler(
            QObject* parent,
            const PathGenerator& pathGenerator,
            qreal speed,
            const MapCoordinates& initialLocation,
            int wanderingCredits
        );

        /**
         * @brief Construct a new motion handler for a targeted character.
         *
         * @param speed             The speed of the character.
         * @param initialLocation   The initial location of the character.
         * @param destination       The idestination of the character.
         * @param restrictedToRoads The wandering credits.
         */
        MotionHandler(
            QObject* parent,
            const PathGenerator& pathGenerator,
            qreal speed,
            const MapCoordinates& initialLocation,
            const MapCoordinates& destination,
            bool restrictedToRoads
        );

        virtual ~MotionHandler();

        /**
         * @brief Set a road target.
         * @deprecated
         */
        void changeDestination(const RoadGraphNode* location);

        /**
         * @brief Set a target.
         */
        void changeDestination(const MapCoordinates& destination);

        /**
         * @brief Reset the destination.
         *
         * The motion will stop at the current location unless another target is set.
         */
        void resetDestination();

        /**
         * @brief Indicate if the motion has used all its wandering credits or has reached the destination.
         */
        bool isPathCompleted() const;

        /**
         * @brief Indicate if the current motion follow the wandering strategy.
         */
        bool isWanderingMotion() const;

        const MapCoordinates& getCurrentLocation() const;

        MapCoordinates getCurrentTileCoordinates() const;

        /**
         * @brief Move and return the new location.
         */
        const MapCoordinates& move();

    private:
        void configureNextMovingStep();

        /**
         * @brief Execute the motion.
         */
        void moveToTarget();
};

#endif // MOTIONHANDLER_HPP
