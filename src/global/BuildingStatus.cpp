#include "BuildingStatus.hpp"

#include <QtCore/QString>

#include "src/exceptions/BadConfigurationException.hpp"



uint qHash(const BuildingStatus& status)
{
    return static_cast<uint>(status);
}



BuildingStatus resolveBuildingStatus(const QString& status)
{
    if (status == "inactive") return BuildingStatus::Inactive;
    if (status == "active")   return BuildingStatus::Active;
    if (status == "working")  return BuildingStatus::Working;

    throw BadConfigurationException("Unknown building status \"" + status + "\".");
}
