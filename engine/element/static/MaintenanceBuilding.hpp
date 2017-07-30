#ifndef MAINTENANCEBUILDING_HPP
#define MAINTENANCEBUILDING_HPP

#include "engine/element/dynamic/RandomWalker.hpp"
#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"

/**
 * @brief A maintenance building for testing purpose.
 */
class MaintenanceBuilding : public AbstractProcessableStaticMapElement
{
        Q_OBJECT

    private:
        CycleDate nextWalkerGenerationDate;
        QList<QPointer<RandomWalker>> walkers;

    public:
        MaintenanceBuilding(QObject* parent, const MapArea& area, const MapCoordinates& entryPoint);

        virtual void init(const CycleDate& date);

        virtual void process(const CycleDate& date);

        virtual void processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor);

    protected:
        void setupNextWalkerGenerationDate(const CycleDate& currentDate);
};

#endif // MAINTENANCEBUILDING_HPP
