#ifndef BUILDINGPROCESSOR_HPP
#define BUILDINGPROCESSOR_HPP

#include <QtCore/QLinkedList>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QPointer>

#include "engine/processing/AbstractProcessable.hpp"

class CycleDate;
class ProcessableBuilding;

/**
 * @brief A processor for all map's buildings.
 */
class BuildingProcessor: public QObject, public AbstractProcessable
{
        Q_OBJECT

    private:
        QLinkedList<QPointer<ProcessableBuilding>> processableList;
        QList<QPointer<ProcessableBuilding>> waitingForRegistrationList;
        QList<ProcessableBuilding*> waitingForUnregistrationList;

    public:
        explicit BuildingProcessor(QObject* parent);

        /**
         * @brief Register a building to be process each time cycle.
         */
        void registerBuilding(ProcessableBuilding* building);

        /**
         * @brief Unregister a building from processor.
         */
        void unregisterBuilding(ProcessableBuilding* building);

        virtual void process(const CycleDate& date) override;
};

#endif // BUILDINGPROCESSOR_HPP
