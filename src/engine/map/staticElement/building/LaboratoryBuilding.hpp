#ifndef LABORATORYBUILDING_HPP
#define LABORATORYBUILDING_HPP

#include <QtCore/QWeakPointer>

#include "src/engine/map/staticElement/building/behavior/WalkerGenerationBehavior.hpp"
#include "src/engine/map/staticElement/building/AbstractProcessableBuilding.hpp"

class Character;
class CharacterGeneratorInterface;

class LaboratoryBuilding : public AbstractProcessableBuilding
{
    private:
        CharacterGeneratorInterface& characterFactory;
        int workingCountDown;
        WalkerGenerationBehavior scientistGeneration;
        QWeakPointer<Character> scientist;

    private:
        LaboratoryBuilding(
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

    protected:
        virtual BuildingStatus getCurrentStatus() const override;

    private:
        /**
         * @brief Indicate if a new miner can be generated.
         */
        bool canGenerateNewWalker() const;
};

#endif // LABORATORYBUILDING_HPP
