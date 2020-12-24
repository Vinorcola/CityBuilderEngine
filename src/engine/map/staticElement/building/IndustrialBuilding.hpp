#ifndef INDUSTRIALBUILDING_HPP
#define INDUSTRIALBUILDING_HPP

#include <QtCore/QWeakPointer>

#include "src/engine/map/staticElement/building/AbstractStoringBuilding.hpp"

class Character;
class CharacterGeneratorInterface;

class IndustrialBuilding : public AbstractStoringBuilding
{
    public:
        static QSharedPointer<AbstractStoringBuilding> Create(
            CharacterGeneratorInterface& characterGenerator,
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

    protected:
        virtual BuildingStatus getCurrentStatus() const override;

    private:
        IndustrialBuilding(
            CharacterGeneratorInterface& characterGenerator,
            const BuildingInformation& conf,
            const TileArea& area,
            Direction orientation,
            const Tile& entryPointTile
        );

        void handleProduction();

    private:
        const int PRODUCTION_INTERVAL;
        CharacterGeneratorInterface& characterGenerator;
        int rawMaterialStock;
        QWeakPointer<Character> deliveryMan;
        int productionCountDown;
};

#endif // INDUSTRIALBUILDING_HPP
