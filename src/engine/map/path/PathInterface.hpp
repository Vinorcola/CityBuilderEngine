#ifndef PATHINTERFACE_HPP
#define PATHINTERFACE_HPP

class MapCoordinates;

/**
 * @brief An interface representing a path that can be followed by a charater.
 */
class PathInterface
{
    public:
        virtual ~PathInterface() {}

        virtual MapCoordinates getNextTargetCoordinates() = 0;
};

#endif // PATHINTERFACE_HPP
