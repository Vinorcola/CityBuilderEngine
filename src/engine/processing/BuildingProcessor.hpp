#ifndef BUILDINGPROCESSOR_HPP
#define BUILDINGPROCESSOR_HPP

#include <QtCore/QList>
#include <QtCore/QSharedPointer>

#include "src/engine/processing/AbstractProcessable.hpp"

class CycleDate;

/**
 * @brief A processor for all map's buildings.
 */
class BuildingProcessor : public AbstractProcessable
{
    private:
        AbstractProcessable& workerHandler;
        QList<QWeakPointer<AbstractProcessable>> entryPointList;
        QHash<const AbstractProcessable*, QWeakPointer<AbstractProcessable>> buildingList;
        QList<QSharedPointer<AbstractProcessable>> waitingForRegistrationList;
        QList<const AbstractProcessable*> waitingForUnregistrationList;

    public:
        BuildingProcessor(AbstractProcessable& workerHandler);

        /**
         * @brief Register a map entry point building.
         */
        void registerMapEntryPoint(const QSharedPointer<AbstractProcessable>& entryPoint);

        /**
         * @brief Register a building to be process each time cycle.
         */
        void registerBuilding(const QSharedPointer<AbstractProcessable>& building);

        /**
         * @brief Unregister a building from processor.
         */
        void unregisterBuilding(const QSharedPointer<AbstractProcessable>& building);

        virtual void process(const CycleDate& date) override;
};

#endif // BUILDINGPROCESSOR_HPP
