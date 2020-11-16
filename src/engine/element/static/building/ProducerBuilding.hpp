#ifndef PRODUCERBUILDING_HPP
#define PRODUCERBUILDING_HPP

#include <QtCore/QList>

#include "src/engine/element/dynamic/character/Character.hpp"
#include "src/engine/element/static/building/AbstractProcessableBuilding.hpp"
#include "src/engine/processing/CycleDate.hpp"

class CharacterFactoryInterface;
class NatureElementSearchEngine;

class ProducerBuilding : public AbstractProcessableBuilding
{
    private:
        const NatureElementSearchEngine& searchEngine;
        CharacterFactoryInterface& characterFactory;
        QList<Reference<Character>> miners;
        CycleDate nextMinerGenerationDate;
        int rawMaterialStock;
        OptionalReference<Character> deliveryMan;

    public:
        ProducerBuilding(
            const NatureElementSearchEngine& searchEngine,
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
         * @brief Clean the miner list in case a miner has been deleted for any reason.
         */
        void cleanMinerList();

        void handleMinerGeneration(const CycleDate& date);

        /**
         * @brief Indicate if a new miner can be generated.
         */
        bool canGenerateNewMiner() const;

        /**
         * @brief Setup the next miner generation date.
         */
        void setupNextMinerGenerationDate(const CycleDate& date);

        void handleProduction();
};

#endif // PRODUCERBUILDING_HPP
