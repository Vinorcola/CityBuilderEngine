#ifndef LABORATORYBUILDING_HPP
#define LABORATORYBUILDING_HPP

#include <QtCore/QWeakPointer>

#include "src/engine/element/static/building/behavior/WalkerGenerationBehavior.hpp"
#include "src/engine/element/static/building/AbstractProcessableBuilding.hpp"
#include "src/engine/processing/CycleDate.hpp"

class Character;
class CharacterFactoryInterface;

class LaboratoryBuilding : public AbstractProcessableBuilding
{
    private:
        CharacterFactoryInterface& characterFactory;
        CycleDate walkerGenerationLimitDate;
        WalkerGenerationBehavior scientistGeneration;
        QWeakPointer<Character> scientist;

    private:
        LaboratoryBuilding(
            CharacterFactoryInterface& characterFactory,
            const BuildingInformation& conf,
            const MapArea& area,
            Direction orientation,
            const MapCoordinates& entryPoint
        );

    public:
        static QSharedPointer<AbstractProcessableBuilding> Create(
            CharacterFactoryInterface& characterFactory,
            const BuildingInformation& conf,
            const MapArea& area,
            Direction orientation,
            const MapCoordinates& entryPoint
        );

        virtual void process(const CycleDate& date) override;
        virtual bool processInteraction(const CycleDate& date, Character& actor) override;

    private:
        /**
         * @brief Indicate if a new miner can be generated.
         */
        bool canGenerateNewWalker() const;
};

#endif // LABORATORYBUILDING_HPP
