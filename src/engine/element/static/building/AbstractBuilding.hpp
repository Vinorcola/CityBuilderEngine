#ifndef ABSTRACTBUILDING_HPP
#define ABSTRACTBUILDING_HPP

#include "src/engine/map/MapArea.hpp"
#include "src/global/reference/Referencable.hpp"

class BuildingInformation;
struct BuildingState;

/**
 * @brief The base class for a static element on the map.
 *
 * A static element is an element that do not move. It covers an area of the map. This area will be blocked to other static
 * elements (two static elements cannot share a piece of area).
 */
class AbstractBuilding : public Referencable
{
    protected:
        const BuildingInformation& conf;
        MapArea area;
        int stateVersion; ///< We use an int for the versionning of the view. Note that an overflow is not dramatic since we always compare versions using equality.

    public:
        AbstractBuilding(const BuildingInformation& conf, const MapArea& area);

        const BuildingInformation& getConf() const;
        virtual BuildingState getCurrentState() const;

    protected:
        void notifyViewDataChange();
};

#endif // ABSTRACTBUILDING_HPP
