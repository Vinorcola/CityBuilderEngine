#ifndef SANITYBUILDING_HPP
#define SANITYBUILDING_HPP

#include <QtCore/QSharedPointer>

#include "src/engine/element/static/building/behavior/WalkerGenerationBehavior.hpp"
#include "src/engine/element/static/building/AbstractProcessableBuilding.hpp"
#include "src/engine/processing/CycleDate.hpp"

class Character;
class CharacterFactoryInterface;

class SanityBuilding : public AbstractProcessableBuilding
{
    private:
        CharacterFactoryInterface& characterFactory;
        WalkerGenerationBehavior walkerGeneration;
        QWeakPointer<Character> walker;

    private:
        SanityBuilding(
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
         * @brief Indicate if a new walker can be generated.
         */
        bool canGenerateNewWalker() const;
};

#endif // SANITYBUILDING_HPP
