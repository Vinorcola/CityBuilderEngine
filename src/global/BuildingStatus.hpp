#ifndef BUILDINGSTATUS_HPP
#define BUILDINGSTATUS_HPP

#include <QtCore/QtGlobal>

/**
 * An enumeration for available building statuses.
 */
enum class BuildingStatus {
    Inactive,
    Active,
    Working,
};

uint qHash(const BuildingStatus& status);

BuildingStatus resolveBuildingStatus(const QString& status);

#endif // BUILDINGSTATUS_HPP
