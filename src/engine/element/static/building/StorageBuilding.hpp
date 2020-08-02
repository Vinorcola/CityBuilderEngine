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

        int storableQuantity(const ItemInformation& itemConf, const int maxQuantity = 1) const;

        virtual void process(const CycleDate& date) override;

        virtual bool processInteraction(const CycleDate& date, Character& actor) override;

    private:
        void store(const ItemInformation& itemConf, const int quantity);
};

#endif // STORAGEBUILDING_HPP
