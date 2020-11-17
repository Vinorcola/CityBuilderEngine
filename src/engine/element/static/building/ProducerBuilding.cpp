#include "ProducerBuilding.hpp"

#include "src/engine/element/dynamic/character/Character.hpp"
#include "src/engine/element/dynamic/character/DeliveryManCharacter.hpp"
#include "src/engine/element/dynamic/character/MinerCharacter.hpp"
#include "src/engine/element/dynamic/CharacterFactoryInterface.hpp"
#include "src/engine/element/static/natureElement/NatureElementSearchEngine.hpp"
#include "src/engine/map/path/PathInterface.hpp"
#include "src/global/conf/BuildingInformation.hpp"



ProducerBuilding::ProducerBuilding(
    const NatureElementSearchEngine& searchEngine,
    CharacterFactoryInterface& characterFactory,
    const BuildingInformation& conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
) :
    AbstractProcessableBuilding(conf, area, entryPoint),
    searchEngine(searchEngine),
    characterFactory(characterFactory),
    miners(),
    nextMinerGenerationDate(),
    rawMaterialStock(0),
    deliveryMan()
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
    miners.cleanAllInvalids();
    handleMinerGeneration(date);
    handleProduction();
}



bool ProducerBuilding::processInteraction(const CycleDate& /*date*/, Character& actor)
{
    auto& issuer(actor.getIssuer());
    if (issuer.isValid() && issuer.matches(*this)) {
        auto miner(dynamic_cast<MinerCharacter*>(&actor));
        if (miner) {
            rawMaterialStock += conf.getProducerConf().miningQuantity;

            return true;
        }

        auto deliveryMan(dynamic_cast<DeliveryManCharacter*>(&actor));
        if (deliveryMan) {
            this->deliveryMan.clear();

            return true;
        }
    }

    return false;
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
        miners.append(miner);

        if (canGenerateNewMiner()) {
            setupNextMinerGenerationDate(date);
        }
        else {
            nextMinerGenerationDate.reset();
        }
    }
    else if (canGenerateNewMiner()) {
        setupNextMinerGenerationDate(date);
    }
}



bool ProducerBuilding::canGenerateNewMiner() const
{
    return miners.length() < conf.getProducerConf().miner.maxSimultaneous;
}



void ProducerBuilding::setupNextMinerGenerationDate(const CycleDate& date)
{
    nextMinerGenerationDate.reassign(date, conf.getProducerConf().miner.generationInterval);
}



void ProducerBuilding::handleProduction()
{
    if (deliveryMan.isNull() && rawMaterialStock >= conf.getProducerConf().rawMaterialQuantityToProduce) {
        deliveryMan.reassign(characterFactory.generateDeliveryMan(
            conf.getProducerConf().deliveryManConf,
            *this,
            conf.getProducerConf().producedItemConf,
            1
        ));
        rawMaterialStock -= conf.getProducerConf().rawMaterialQuantityToProduce;
    }
}
