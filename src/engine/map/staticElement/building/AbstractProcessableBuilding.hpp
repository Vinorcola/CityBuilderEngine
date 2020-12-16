#ifndef ABSTRACTPROCESSABLEBUILDING_HPP
#define ABSTRACTPROCESSABLEBUILDING_HPP

#include <QtCore/QWeakPointer>

#include "src/engine/map/staticElement/building/AbstractBuilding.hpp"
#include "src/engine/processing/AbstractProcessable.hpp"
#include "src/global/geometry/TileCoordinates.hpp"
#include "src/global/BuildingStatus.hpp"

class BuildingInformation;
class Character;

class AbstractProcessableBuilding : public AbstractBuilding, public AbstractProcessable
{
    private:
        TileCoordinates entryPoint;
        int currentWorkerQuantity;

    protected:
        QWeakPointer<AbstractProcessableBuilding> selfReference;

    protected:
        AbstractProcessableBuilding(
            const BuildingInformation& conf,
            const TileArea& area,
            Direction orientation,
            const TileCoordinates& entryPoint
        );

    public:
        QWeakPointer<AbstractProcessableBuilding> getSelfReference() const;
        const TileCoordinates& getEntryPoint() const;
        bool isActive() const;

        void assignWorkers(int workerQuantity);

        virtual bool processInteraction(const CycleDate& date, Character& actor);

        virtual BuildingState getCurrentState() const override;

    protected:
        int getCurrentWorkerQuantity() const;
        virtual BuildingStatus getCurrentStatus() const;
};

#endif // ABSTRACTPROCESSABLEBUILDING_HPP
