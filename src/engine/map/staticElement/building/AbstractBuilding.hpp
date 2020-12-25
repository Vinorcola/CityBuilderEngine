#ifndef ABSTRACTBUILDING_HPP
#define ABSTRACTBUILDING_HPP

#include "src/engine/map/staticElement/AbstractStaticElement.hpp"
#include "src/global/geometry/TileArea.hpp"
#include "src/global/Direction.hpp"

class BuildingInformation;
struct BuildingState;

/**
 * @brief The base class for a static element on the map.
 *
 * A static element is an element that do not move. It covers an area of the map. This area will be blocked to other static
 * elements (two static elements cannot share a piece of area).
 */
class AbstractBuilding : public AbstractStaticElement
{
    protected:
        const BuildingInformation& conf;
        const TileArea area;
        const Direction orientation;
        int stateVersion; ///< We use an int for the versionning of the view. Note that an overflow is not dramatic since we always compare versions using equality.

    public:
        AbstractBuilding(const BuildingInformation& conf, const TileArea& area, Direction orientation);
        virtual ~AbstractBuilding();

        const BuildingInformation& getConf() const;
        virtual BuildingState getCurrentState() const;

    protected:
        void notifyViewDataChange();
};

#endif // ABSTRACTBUILDING_HPP
