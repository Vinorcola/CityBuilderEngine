#ifndef PROCESSABLEBUILDING_HPP
#define PROCESSABLEBUILDING_HPP

#include <QtCore/QObject>

#include "src/engine/element/static/Building.hpp"
#include "src/engine/map/MapCoordinates.hpp"
#include "src/engine/processing/AbstractProcessable.hpp"

class BuildingInformation;
class Character;
class MapAreea;

class ProcessableBuilding : public Building, public AbstractProcessable
{
        Q_OBJECT

    private:
        MapCoordinates entryPoint;

    public:
        ProcessableBuilding(
            QObject* parent,
            const BuildingInformation& conf,
            const MapArea& area,
            const MapCoordinates& entryPoint
        );

        const MapCoordinates& getEntryPoint() const;

        virtual bool processInteraction(const CycleDate& date, Character* actor);
};

#endif // PROCESSABLEBUILDING_HPP
