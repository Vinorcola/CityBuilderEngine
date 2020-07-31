#ifndef PRODUCERBUILDING_HPP
#define PRODUCERBUILDING_HPP

#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QPointer>

#include "src/engine/element/static/ProcessableBuilding.hpp"
#include "src/engine/processing/CycleDate.hpp"

class BuildingInformation;
class CharacterFactoryInterface;
class CharacterInformation;
class ItemInformation;
class MapArea;
class MapCoordinates;
class MapSearchEngine;
class NatureElementInformation;

class ProducerBuilding : public ProcessableBuilding
{
        Q_OBJECT

    private:
        const MapSearchEngine& searchEngine;
        CharacterFactoryInterface& characterFactory;
        QList<QPointer<Character>> miners;
        CycleDate nextMinerGenerationDate;
        int rawMaterialStock;

    public:
        ProducerBuilding(
            QObject* parent,
            const MapSearchEngine& searchEngine,
            CharacterFactoryInterface& characterFactory,
            const BuildingInformation& conf,
            const MapArea& area,
            const MapCoordinates& entryPoint
        );

        virtual void init(const CycleDate& date) override;

        virtual void process(const CycleDate& date) override;

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
};

#endif // PRODUCERBUILDING_HPP
