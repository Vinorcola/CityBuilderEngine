#ifndef WORKINGPLACEREGISTRYINTERFACE_HPP
#define WORKINGPLACEREGISTRYINTERFACE_HPP

#include <QtCore/QSharedPointer>

class AbstractProcessableBuilding;

/**
 * @brief An interface for working places registry.
 */
class WorkingPlaceRegistryInterface
{
    public:
        virtual ~WorkingPlaceRegistryInterface() {};

        virtual void registerWorkingPlace(const QSharedPointer<AbstractProcessableBuilding>& workingPlace) = 0;
        virtual void unregisterWorkingPlace(const QSharedPointer<AbstractProcessableBuilding>& workingPlace) = 0;
};

#endif // WORKINGPLACEREGISTRYINTERFACE_HPP
