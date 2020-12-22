#ifndef PRODUCERBUILDING_HPP
#define PRODUCERBUILDING_HPP

#include <QtCore/QHash>
#include <QtCore/QWeakPointer>

#include "src/engine/map/staticElement/building/behavior/WalkerGenerationBehavior.hpp"
#include "src/engine/map/staticElement/building/AbstractProcessableBuilding.hpp"
#include "src/engine/processing/CycleDate.hpp"
#include "src/global/BuildingStatus.hpp"

class Character;
class CharacterGeneratorInterface;
class NatureElementSearchEngine;

class ProducerBuilding : public AbstractProcessableBuilding
{
    private:
        const NatureElementSearchEngine& searchEngine;
        CharacterGeneratorInterface& characterFactory;
        WalkerGenerationBehavior minerGeneration;
        QHash<Character*, QWeakPointer<Character>> miners;
        int rawMaterialStock;
        QWeakPointer<Character> deliveryMan;

    private:
        ProducerBuilding(
            const NatureElementSearchEngine& searchEngine,
            CharacterGeneratorInterface& characterFactory,
            const BuildingInformation& conf,
            const TileArea& area,
            Direction orientation,
            const Tile& entryPointTile
        );

    public:
        static QSharedPointer<AbstractProcessableBuilding> Create(
            const NatureElementSearchEngine& searchEngine,
            CharacterGeneratorInterface& characterFactory,
            const BuildingInformation& conf,
            const TileArea& area,
            Direction orientation,
            const Tile& entryPointTile
        );

        virtual void process(const CycleDate& date) override;
        virtual bool processInteraction(const CycleDate& date, Character& actor) override;

        virtual BuildingState getCurrentState() const override;

    protected:
        virtual BuildingStatus getCurrentStatus() const override;

    private:
        void handleMinerGeneration(const CycleDate& date);

        /**
         * @brief Indicate if a new miner can be generated.
         */
        bool canGenerateNewMiner() const;

        void handleProduction();
};

#endif // PRODUCERBUILDING_HPP
