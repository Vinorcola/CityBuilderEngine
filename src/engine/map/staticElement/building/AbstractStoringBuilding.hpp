#ifndef ABSTRACTSTORINGBUILDING_HPP
#define ABSTRACTSTORINGBUILDING_HPP

#include "src/engine/map/staticElement/building/AbstractProcessableBuilding.hpp"

class ItemInformation;

class AbstractStoringBuilding : public AbstractProcessableBuilding
{
    public:
        AbstractStoringBuilding(
            const BuildingInformation& conf,
            const TileArea& area,
            Direction orientation,
            const Tile& entryPointTile
        );

        /**
         * @brief Indicate if the building require the given item.
         */
        virtual bool require(const ItemInformation& itemConf) const = 0;

        /**
         * @brief Return the max storable quantity of the given item.
         */
        virtual int storableQuantity(const ItemInformation& itemConf) const = 0;
};

#endif // ABSTRACTSTORINGBUILDING_HPP
