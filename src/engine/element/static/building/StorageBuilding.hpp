#ifndef STORAGEBUILDING_HPP
#define STORAGEBUILDING_HPP

#include <QtCore/QHash>

#include "src/engine/element/static/ProcessableBuilding.hpp"

class ItemInformation;

class StorageBuilding : public ProcessableBuilding
{
        Q_OBJECT

    private:
        QHash<const ItemInformation*, int> stock;

    public:
        StorageBuilding(
            QObject* parent,
            const BuildingInformation& conf,
            const MapArea& area,
            const MapCoordinates& entryPoint
        );

        virtual void process(const CycleDate& date) override;
};

#endif // STORAGEBUILDING_HPP
