#ifndef SANITYBUILDING_HPP
#define SANITYBUILDING_HPP

#include <QtCore/QSharedPointer>

#include "src/engine/map/staticElement/building/behavior/WalkerGenerationBehavior.hpp"
#include "src/engine/map/staticElement/building/AbstractProcessableBuilding.hpp"
#include "src/engine/processing/CycleDate.hpp"

class Character;
class CharacterGeneratorInterface;

class SanityBuilding : public AbstractProcessableBuilding
{
    private:
        CharacterGeneratorInterface& characterFactory;
        WalkerGenerationBehavior walkerGeneration;
        QWeakPointer<Character> walker;

    private:
        SanityBuilding(
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

    private:
        /**
         * @brief Indicate if a new walker can be generated.
         */
        bool canGenerateNewWalker() const;
};

#endif // SANITYBUILDING_HPP
