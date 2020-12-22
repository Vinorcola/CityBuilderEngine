#ifndef MOTIONHANDLER_HPP
#define MOTIONHANDLER_HPP

#include <QtCore/QSharedPointer>

#include "src/global/geometry/DynamicElementCoordinates.hpp"
#include "src/global/Direction.hpp"

class PathInterface;
class Tile;

/**
 * @brief Handle the motion of characters on the map.
 */
class MotionHandler
{
    private:
        const qreal speed;
        QSharedPointer<PathInterface> path;///< The path to follow.
        DynamicElementCoordinates location;///< The current coordinates of the element.
        const Tile* movingFrom;///< The tile the element is moving from.
        const Tile* movingTo;///< The tile the element is moving to.
        Direction direction;///< The direction the character is going to.

    public:
        /**
         * @brief Construct a new motion handler.
         *
         * @param speed       The speed of the character.
         * @param initialTile The initial tile of the character.
         */
        MotionHandler(const qreal speed, const Tile& initialTile);

        const DynamicElementCoordinates& getCurrentLocation() const;
        const Tile& getCurrentTile() const;
        Direction getCurrentDirection() const;
        bool isPathObsolete() const;
        bool isPathCompleted() const;

        void takePath(QSharedPointer<PathInterface> path);

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
        Direction resolveDirection();
};

#endif // MOTIONHANDLER_HPP
