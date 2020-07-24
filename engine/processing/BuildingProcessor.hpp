#ifndef BUILDINGPROCESSOR_HPP
#define BUILDINGPROCESSOR_HPP

#include <QtCore/QLinkedList>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QPointer>

#include "engine/processing/AbstractProcessable.hpp"

class AbstractProcessableStaticMapElement;
class CycleDate;

/**
 * @brief A processor for all map's buildings.
 */
class BuildingProcessor: public QObject, public AbstractProcessable
{
        Q_OBJECT

    private:
        QLinkedList<QPointer<AbstractProcessableStaticMapElement>> processableList;
        QList<QPointer<AbstractProcessableStaticMapElement>> waitingForRegistrationList;
        QList<AbstractProcessableStaticMapElement*> waitingForUnregistrationList;

    public:
        explicit BuildingProcessor(QObject* parent);

        /**
         * @brief Register a building to be process each time cycle.
         */
        void registerBuilding(AbstractProcessableStaticMapElement* building);

        /**
         * @brief Unregister a building from processor.
         */
        void unregisterBuilding(AbstractProcessableStaticMapElement* building);

        virtual void process(const CycleDate& date) override;
};

#endif // BUILDINGPROCESSOR_HPP
