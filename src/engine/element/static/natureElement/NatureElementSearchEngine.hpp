#ifndef NATUREELEMENTSEARCHENGINE_HPP
#define NATUREELEMENTSEARCHENGINE_HPP

#include "src/defines.hpp"

class MapCoordinates;
class NatureElementInformation;
class PathInterface;

class NatureElementSearchEngine
{
    public:
        NatureElementSearchEngine();

        optional<owner<PathInterface*>> getPathToClosestRawMaterial(
            const NatureElementInformation& conf,
            const MapCoordinates& origin
        ) const;
};

#endif // NATUREELEMENTSEARCHENGINE_HPP
