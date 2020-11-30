#ifndef FARMBUILDING_HPP
#define FARMBUILDING_HPP

#include <QtCore/QWeakPointer>

#include "src/engine/element/static/building/AbstractProcessableBuilding.hpp"

class CharacterFactoryInterface;
class ItemInformation;

class FarmBuilding : public AbstractProcessableBuilding
{
    private:
        const int GROWING_INTERVAL;
        CharacterFactoryInterface& characterFactory;
        int growingCountDown;
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

        virtual void process(const CycleDate& date) override;
        virtual bool processInteraction(const CycleDate& date, Character& actor) override;

        virtual BuildingState getCurrentState() const override;

    private:
        qreal getGrowthRatio() const;
        void harvest();
};

#endif // FARMBUILDING_HPP
