#ifndef SCHOOLBUILDING_HPP
#define SCHOOLBUILDING_HPP

#include "src/engine/element/static/ProcessableBuilding.hpp"

/**
 * @brief A school building will generate student at a regular interval as long as there is a university accepting them.
 */
class SchoolBuilding : public ProcessableBuilding
{
        Q_OBJECT

    public:
        SchoolBuilding(
            QObject* parent,
            const BuildingInformation& conf,
            const MapArea& area,
            const MapCoordinates& entryPoint
        );

        virtual void process(const CycleDate& date) override;
};

#endif // SCHOOLBUILDING_HPP
