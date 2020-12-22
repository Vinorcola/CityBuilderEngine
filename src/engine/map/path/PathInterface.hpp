#ifndef PATHINTERFACE_HPP
#define PATHINTERFACE_HPP

#include "src/defines.hpp"

class Tile;

/**
 * @brief An interface representing a path that can be followed by a charater.
 */
class PathInterface
{
    public:
        virtual ~PathInterface() {}

        /**
         * @brief Indicate if the path is obsolete.
         *
         * An obsolete path can occur when some of it's tiles are occupied (e.i. constructions).
         */
        virtual bool isObsolete() const = 0;
        virtual bool isCompleted() const = 0;

        virtual bool isNextTileValid() const = 0;
        virtual const Tile& getNextTile() = 0;
};

#endif // PATHINTERFACE_HPP
