#ifndef MOTIONHANDLER_HPP
#define MOTIONHANDLER_HPP

#include <QtCore/QSharedPointer>

#include "src/engine/map/MapCoordinates.hpp"
#include "src/global/Direction.hpp"

class PathInterface;

/**
 * @brief Handle the motion of characters on the map.
 */
class MotionHandler
{
    private:
        const qreal speed;
        QSharedPointer<PathInterface> path;///< The path to follow.
        MapCoordinates location;///< The current coordinates of the element.
        MapCoordinates movingFrom;///< The coordinates of the tile the element is moving from.
        MapCoordinates movingTo;///< The coordinates of the tile the element is moving to.
        Direction direction;///< The direction the character is going to.

    public:
        /**
         * @brief Construct a new motion handler.
         *
         * @param speed                The speed of the character.
         * @param initialLocation      The initial location of the character.
         */
        MotionHandler(const qreal speed, const MapCoordinates& initialLocation);

        const MapCoordinates& getCurrentLocation() const;
        Direction getCurrentDirection() const;
        MapCoordinates getCurrentTileCoordinates() const;
        bool isPathObsolete() const;
        bool isPathCompleted() const;

        void takePath(QSharedPointer<PathInterface> path);

        /**
         * @brief Stop the motion and reset any data about the motion.
         *
         * The motion will stop at the current location unless another target is set. The path followed is reset.
         */
        void stop();

        /**
         * @brief Move and return the new location.
         * @return `true` if the location has changed.
         */
        bool move();

    private:
        /**
         * @brief Execute the motion.
         * @return `true` if the location has changed.
         */
        bool moveToTarget();
        void updateDirection();
};

#endif // MOTIONHANDLER_HPP
