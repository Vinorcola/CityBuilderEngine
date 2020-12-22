#ifndef FARMBUILDING_HPP
#define FARMBUILDING_HPP

#include <QtCore/QWeakPointer>

#include "src/engine/map/staticElement/building/AbstractProcessableBuilding.hpp"

class CharacterGeneratorInterface;
class ItemInformation;

class FarmBuilding : public AbstractProcessableBuilding
{
    private:
        const int GROWING_INTERVAL;
        CharacterGeneratorInterface& characterFactory;
        int growingCountDown;
        QWeakPointer<Character> deliveryMan;

    private:
        FarmBuilding(
            CharacterGeneratorInterface& characterFactory,
            const BuildingInformation& conf,
            const TileArea& area,
            Direction orientation,
            const Tile& entryPointTile
        );

    public:
        static QSharedPointer<AbstractProcessableBuilding> Create(
            CharacterGeneratorInterface& characterFactory,
            const BuildingInformation& conf,
            const TileArea& area,
            Direction orientation,
            const Tile& entryPointTile
        );

        virtual void process(const CycleDate& date) override;
        virtual bool processInteraction(const CycleDate& date, Character& actor) override;

        virtual BuildingState getCurrentState() const override;

    private:
        qreal getGrowthRatio() const;
        void harvest();
};

#endif // FARMBUILDING_HPP
