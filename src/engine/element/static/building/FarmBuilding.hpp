#ifndef FARMBUILDING_HPP
#define FARMBUILDING_HPP

#include <QtCore/QWeakPointer>

#include "src/engine/element/static/building/AbstractProcessableBuilding.hpp"
#include "src/engine/processing/CycleDate.hpp"

class CharacterFactoryInterface;
class ItemInformation;

class FarmBuilding : public AbstractProcessableBuilding
{
    private:
        CharacterFactoryInterface& characterFactory;
        CycleDate completeGrowingDate;
        QWeakPointer<Character> deliveryMan;

    private:
        FarmBuilding(
            CharacterFactoryInterface& characterFactory,
            const BuildingInformation& conf,
            const MapArea& area,
            const MapCoordinates& entryPoint
        );

    public:
        static QSharedPointer<AbstractProcessableBuilding> Create(
            CharacterFactoryInterface& characterFactory,
            const BuildingInformation& conf,
            const MapArea& area,
            const MapCoordinates& entryPoint
        );

        virtual void init(const CycleDate& date) override;
        virtual void process(const CycleDate& date) override;
        virtual bool processInteraction(const CycleDate& date, Character& actor) override;

        virtual BuildingState getCurrentState() const override;

    private:
        void harvest(const CycleDate& date);
};

#endif // FARMBUILDING_HPP
