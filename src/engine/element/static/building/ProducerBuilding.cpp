#include "ProducerBuilding.hpp"

#include "src/engine/element/dynamic/character/MinerCharacter.hpp"
#include "src/engine/element/dynamic/Character.hpp"
#include "src/engine/element/dynamic/CharacterFactoryInterface.hpp"
#include "src/engine/map/path/PathInterface.hpp"
#include "src/engine/map/MapSearchEngine.hpp"
#include "src/global/conf/BuildingInformation.hpp"



ProducerBuilding::ProducerBuilding(
    QObject* parent,
    const MapSearchEngine& searchEngine,
    CharacterFactoryInterface& characterFactory,
    const BuildingInformation& conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
) :
    ProcessableBuilding(parent, conf, area, entryPoint),
    searchEngine(searchEngine),
    characterFactory(characterFactory),
    miners(),
    nextMinerGenerationDate(),
    rawMaterialStock(0)
{

}



void ProducerBuilding::init(const CycleDate& date)
{
    if (canGenerateNewMiner()) {
        setupNextMinerGenerationDate(date);
    }
}



void ProducerBuilding::process(const CycleDate& date)
{
    cleanMinerList();
    handleMinerGeneration(date);
}



bool ProducerBuilding::processInteraction(const CycleDate& /*date*/, Character& actor)
{
    if (miners.contains(&actor)) {
        rawMaterialStock += conf.getProducerConf().miningQuantity;
        characterFactory.clearCharacter(actor);

        return true;
    }

    return false;
}



void ProducerBuilding::cleanMinerList()
{
    auto iterator(miners.begin());
    auto end(miners.end());
    while (iterator != end) {
        if (iterator->isNull()) {
            iterator = miners.erase(iterator);
        } else {
            ++iterator;
        }
    }
}



void ProducerBuilding::handleMinerGeneration(const CycleDate& date)
{
    if (nextMinerGenerationDate) {
        if (date < nextMinerGenerationDate) {
            return;
        }

        auto path(searchEngine.getPathToClosestRawMaterial(conf.getProducerConf().rawMaterialConf, getEntryPoint()));
        if (!path) {
            // We don't have any target free for now.
            setupNextMinerGenerationDate(date);
            return;
        }

        auto& miner(characterFactory.generateMiner(conf.getProducerConf().miner.conf, *this, path));
        connect(&miner, &MinerCharacter::hasFinishedHarvest, [&miner]() {
            miner.goHome();
        });
        miners.append(&miner);

        if (canGenerateNewMiner()) {
            setupNextMinerGenerationDate(date);
        }
        else {
            nextMinerGenerationDate.reset();
        }
    }
    else {
        if (canGenerateNewMiner()) {
            setupNextMinerGenerationDate(date);
        }
    }
}



bool ProducerBuilding::canGenerateNewMiner() const
{
    return miners.size() < conf.getProducerConf().miner.maxSimultaneous;
}



void ProducerBuilding::setupNextMinerGenerationDate(const CycleDate& date)
{
    nextMinerGenerationDate.reassign(date, conf.getProducerConf().miner.generationInterval);
}
