#ifndef PRODUCERBUILDING_HPP
#define PRODUCERBUILDING_HPP

#include <QtCore/QObject>

#include "src/engine/element/static/ProcessableBuilding.hpp"

class BuildingInformation;
class CharacterInformation;
class ItemInformation;
class mapArea;
class mapCoordinates;
class NatureElementInformation;

class ProducerBuilding : public ProcessableBuilding
{
        Q_OBJECT

    private:
        int rawMaterialStock;

    public:
        ProducerBuilding(
            QObject* parent,
            const BuildingInformation& conf,
            const MapArea& area,
            const MapCoordinates& entryPoint
        );

        virtual void process(const CycleDate& date) override;
};

#endif // PRODUCERBUILDING_HPP
