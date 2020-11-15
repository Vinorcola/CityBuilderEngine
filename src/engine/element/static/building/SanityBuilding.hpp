#ifndef SANITYBUILDING_HPP
#define SANITYBUILDING_HPP

#include <QtCore/QPointer>

#include "src/engine/element/static/building/AbstractProcessableBuilding.hpp"
#include "src/engine/processing/CycleDate.hpp"

class CharacterFactoryInterface;

class SanityBuilding : public AbstractProcessableBuilding
{
    private:
        CharacterFactoryInterface& characterFactory;
        QPointer<Character> walker;
        CycleDate nextWalkerGenerationDate;

    public:
        SanityBuilding(
            CharacterFactoryInterface& characterFactory,
            const BuildingInformation& conf,
            const MapArea& area,
            const MapCoordinates& entryPoint
        );

        virtual void init(const CycleDate& date) override;

        virtual void process(const CycleDate& date) override;

        virtual bool processInteraction(const CycleDate& date, Character& actor) override;

    private:
        /**
         * @brief Indicate if a new miner can be generated.
         */
        bool canGenerateNewWalker() const;

        /**
         * @brief Setup the next miner generation date.
         */
        void setupNextWalkerGenerationDate(const CycleDate& date);
};

#endif // SANITYBUILDING_HPP
