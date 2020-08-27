#ifndef LABORATORYBUILDING_HPP
#define LABORATORYBUILDING_HPP

#include "src/engine/element/static/ProcessableBuilding.hpp"

class LaboratoryBuilding : public ProcessableBuilding
{
        Q_OBJECT

    public:
        LaboratoryBuilding(
            QObject* parent,
            const BuildingInformation& conf,
            const MapArea& area,
            const MapCoordinates& entryPoint
        );

        virtual void process(const CycleDate& date) override;
};

#endif // LABORATORYBUILDING_HPP
