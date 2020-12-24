#ifndef STORAGEBUILDING_HPP
#define STORAGEBUILDING_HPP

#include <QtCore/QHash>

#include "src/engine/map/staticElement/building/AbstractStoringBuilding.hpp"

class ItemInformation;

class StorageBuilding : public AbstractStoringBuilding
{
    private:
        QHash<const ItemInformation*, int> stock;

    private:
        StorageBuilding(
            const BuildingInformation& conf,
            const TileArea& area,
            Direction orientation,
            const Tile& entryPointTile
        );

    public:
        static QSharedPointer<AbstractStoringBuilding> Create(
            const BuildingInformation& conf,
            const TileArea& area,
            Direction orientation,
            const Tile& entryPointTile
        );

        virtual bool require(const ItemInformation& itemConf) const override;
        virtual int storableQuantity(const ItemInformation& itemConf) const override;

        virtual void process(const CycleDate& date) override;
        virtual bool processInteraction(const CycleDate& date, Character& actor) override;

        virtual BuildingState getCurrentState() const override;

    private:
        void store(const ItemInformation& itemConf, const int quantity);
};

#endif // STORAGEBUILDING_HPP
