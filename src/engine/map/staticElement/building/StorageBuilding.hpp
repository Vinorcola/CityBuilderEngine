#ifndef STORAGEBUILDING_HPP
#define STORAGEBUILDING_HPP

#include <QtCore/QHash>

#include "src/engine/map/staticElement/building/AbstractProcessableBuilding.hpp"

class ItemInformation;

class StorageBuilding : public AbstractProcessableBuilding
{
    private:
        QHash<const ItemInformation*, int> stock;

    private:
        StorageBuilding(
            const BuildingInformation& conf,
            const MapArea& area,
            Direction orientation,
            const MapCoordinates& entryPoint
        );

    public:
        static QSharedPointer<StorageBuilding> Create(
            const BuildingInformation& conf,
            const MapArea& area,
            Direction orientation,
            const MapCoordinates& entryPoint
        );

        int storableQuantity(const ItemInformation& itemConf, const int maxQuantity = 1) const;

        virtual void process(const CycleDate& date) override;
        virtual bool processInteraction(const CycleDate& date, Character& actor) override;

        virtual BuildingState getCurrentState() const override;

    private:
        void store(const ItemInformation& itemConf, const int quantity);
};

#endif // STORAGEBUILDING_HPP
