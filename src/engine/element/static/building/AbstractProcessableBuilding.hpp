#ifndef ABSTRACTPROCESSABLEBUILDING_HPP
#define ABSTRACTPROCESSABLEBUILDING_HPP

#include <QtCore/QWeakPointer>

#include "src/engine/element/static/building/AbstractBuilding.hpp"
#include "src/engine/map/MapCoordinates.hpp"
#include "src/engine/processing/AbstractProcessable.hpp"

class BuildingInformation;
class Character;
class MapAreea;

class AbstractProcessableBuilding : public AbstractBuilding, public AbstractProcessable
{
    private:
        MapCoordinates entryPoint;
        int currentWorkerQuantity;

    protected:
        QWeakPointer<AbstractProcessableBuilding> selfReference;

    protected:
        AbstractProcessableBuilding(
            const BuildingInformation& conf,
            const MapArea& area,
            const MapCoordinates& entryPoint
        );

    public:
        QWeakPointer<AbstractProcessableBuilding> getSelfReference() const;
        const MapCoordinates& getEntryPoint() const;

        void assignWorkers(int workerQuantity);

        virtual bool processInteraction(const CycleDate& date, Character& actor);

        virtual BuildingState getCurrentState() const override;

    protected:
        int getCurrentWorkerQuantity() const;
        qreal getWorkingRatio() const;
};

#endif // ABSTRACTPROCESSABLEBUILDING_HPP
