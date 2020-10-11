#ifndef BUILDING_HPP
#define BUILDING_HPP

#include <QtCore/QObject>

#include "src/engine/map/MapArea.hpp"

class BuildingInformation;

/**
 * @brief The base class for a static element on the map.
 *
 * A static element is an element that do not move. It covers an area of the map. This area will be blocked to other static
 * elements (two static elements cannot share a piece of area).
 */
class Building: public QObject
{
        Q_OBJECT

    protected:
        const BuildingInformation& conf;
        MapArea area;
        int viewVersion;///< We use an int for the versionning of the view. Note that an overflow is not dramatic since we always compare versions using equality.

    public:
        Building(QObject* parent, const BuildingInformation& conf, const MapArea& area);

        const BuildingInformation& getConf() const;

        const MapArea& getArea() const;

        bool isViewUpToDate(const int currentViewVersion) const;

        int getViewVersion() const;

    protected:
        void notifyViewDataChange();
};

#endif // BUILDING_HPP
