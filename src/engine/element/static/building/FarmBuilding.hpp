#ifndef FARMBUILDING_HPP
#define FARMBUILDING_HPP

#include <QtCore/QPointer>

#include "src/engine/element/static/ProcessableBuilding.hpp"
#include "src/engine/processing/CycleDate.hpp"

class CharacterFactoryInterface;
class DeliveryManCharacter;
class ItemInformation;

class FarmBuilding : public ProcessableBuilding
{
        Q_OBJECT

    private:
        CharacterFactoryInterface& characterFactory;
        CycleDate completeGrowingDate;
        QPointer<DeliveryManCharacter> deliveryMan;

    public:
        FarmBuilding(
            QObject* parent,
            CharacterFactoryInterface& characterFactory,
            const BuildingInformation& conf,
            const MapArea& area,
            const MapCoordinates& entryPoint
        );

        virtual void init(const CycleDate& date) override;

        virtual void process(const CycleDate& date) override;

        virtual bool processInteraction(const CycleDate& date, Character& actor) override;

    private:
        void harvest(const CycleDate& date);
};

#endif // FARMBUILDING_HPP
