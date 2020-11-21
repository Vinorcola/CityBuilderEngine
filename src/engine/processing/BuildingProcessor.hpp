#ifndef BUILDINGPROCESSOR_HPP
#define BUILDINGPROCESSOR_HPP

#include <QtCore/QList>
#include <QtCore/QSharedPointer>

#include "src/engine/processing/AbstractProcessable.hpp"

class AbstractProcessableBuilding;
class CycleDate;

/**
 * @brief A processor for all map's buildings.
 */
class BuildingProcessor : public AbstractProcessable
{
    private:
        AbstractProcessable& populationHandler;
        QHash<const AbstractProcessableBuilding*, QWeakPointer<AbstractProcessableBuilding>> processableList;
        QList<QSharedPointer<AbstractProcessableBuilding>> waitingForRegistrationList;
        QList<const AbstractProcessableBuilding*> waitingForUnregistrationList;

    public:
        BuildingProcessor(AbstractProcessable& populationHandler);

        /**
         * @brief Register a building to be process each time cycle.
         */
        void registerBuilding(const QSharedPointer<AbstractProcessableBuilding>& building);

        /**
         * @brief Unregister a building from processor.
         */
        void unregisterBuilding(const QSharedPointer<AbstractProcessableBuilding>& building);

        virtual void init(const CycleDate& date) override;
        virtual void process(const CycleDate& date) override;
};

#endif // BUILDINGPROCESSOR_HPP
