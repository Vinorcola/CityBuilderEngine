#ifndef BUILDINGPROCESSOR_HPP
#define BUILDINGPROCESSOR_HPP

#include <QtCore/QList>

#include "src/engine/element/static/building/AbstractProcessableBuilding.hpp"
#include "src/global/reference/collection/ReferenceCollection.hpp"

class CycleDate;

/**
 * @brief A processor for all map's buildings.
 */
class BuildingProcessor : public AbstractProcessable
{
    private:
        ReferenceCollection<AbstractProcessableBuilding> processableList;
        ReferenceCollection<AbstractProcessableBuilding> waitingForRegistrationList;
        QList<AbstractProcessableBuilding*> waitingForUnregistrationList;

    public:
        BuildingProcessor();

        /**
         * @brief Register a building to be process each time cycle.
         */
        void registerBuilding(AbstractProcessableBuilding& building);

        /**
         * @brief Unregister a building from processor.
         */
        void unregisterBuilding(AbstractProcessableBuilding& building);

        virtual void process(const CycleDate& date) override;
};

#endif // BUILDINGPROCESSOR_HPP
