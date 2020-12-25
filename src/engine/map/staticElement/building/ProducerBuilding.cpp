#include "ProducerBuilding.hpp"

#include "src/engine/map/dynamicElement/character/Character.hpp"
#include "src/engine/map/dynamicElement/character/DeliveryManCharacter.hpp"
#include "src/engine/map/dynamicElement/character/MinerCharacter.hpp"
#include "src/engine/map/dynamicElement/CharacterGeneratorInterface.hpp"
#include "src/engine/map/path/PathInterface.hpp"
#include "src/engine/map/staticElement/natureElement/NatureElementSearchEngine.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/pointer/SmartPointerUtils.hpp"
#include "src/global/state/BuildingState.hpp"



QSharedPointer<AbstractProcessableBuilding> ProducerBuilding::Create(
    const NatureElementSearchEngine& searchEngine,
    CharacterGeneratorInterface& characterFactory,
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const Tile& entryPointTile
) {
    auto producer(new ProducerBuilding(searchEngine, characterFactory, conf, area, orientation, entryPointTile));
    QSharedPointer<AbstractProcessableBuilding> pointer(producer);
    producer->selfReference = pointer;

    return pointer;
}



void ProducerBuilding::process(const CycleDate& /*date*/)
{
    if (!isActive()) {
        return;
    }

    cleanInvalids(miners);
    handleMinerGeneration();

    if (rawMaterialStock >= conf.getProducerConf().requiredQuantityForProduction) {
        if (productionCountDown > 0) {
            productionCountDown -= getCurrentWorkerQuantity();
            notifyViewDataChange();
        }
        if (productionCountDown <= 0) {
            handleProduction();
        }
    }
}



bool ProducerBuilding::processInteraction(const CycleDate& /*date*/, Character& actor)
{
    if (matches(deliveryMan, actor)) {
        deliveryMan.clear();

        return true;
    }

    if (miners.contains(&actor)) {
        rawMaterialStock += conf.getProducerConf().miningQuantity;
        miners.remove(&actor);
        notifyViewDataChange();

        return true;
    }

    return false;
}



BuildingState ProducerBuilding::getCurrentState() const
{
    return BuildingState::CreateProducerState(
        reinterpret_cast<qintptr>(this),
        conf,
        area,
        orientation,
        getCurrentStatus(),
        getCurrentWorkerQuantity(),
        stateVersion,
        rawMaterialStock,
        static_cast<int>(
            100.0 *
            static_cast<qreal>(PRODUCTION_INTERVAL - productionCountDown) / static_cast<qreal>(PRODUCTION_INTERVAL)
        )
    );
}



BuildingStatus ProducerBuilding::getCurrentStatus() const
{
    if (!isActive()) {
        return BuildingStatus::Inactive;
    }
    if (rawMaterialStock > 0) {
        return BuildingStatus::Working;
    }

    return BuildingStatus::Active;
}



ProducerBuilding::ProducerBuilding(
    const NatureElementSearchEngine& searchEngine,
    CharacterGeneratorInterface& characterFactory,
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const Tile& entryPointTile
) :
    AbstractProcessableBuilding(conf, area, orientation, entryPointTile),
    PRODUCTION_INTERVAL(conf.getProducerConf().productionInterval * conf.getMaxWorkers()),
    searchEngine(searchEngine),
    characterFactory(characterFactory),
    minerGeneration(conf.getMaxWorkers(), conf.getProducerConf().miner.generationInterval),
    miners(),
    rawMaterialStock(0),
    deliveryMan(),
    productionCountDown(PRODUCTION_INTERVAL)
{

}



void ProducerBuilding::handleMinerGeneration()
{
    if (!canGenerateNewMiner()) {
        return;
    }

    minerGeneration.process(getCurrentWorkerQuantity());
    if (minerGeneration.isReadyToGenerateWalker()) {
        auto path(searchEngine.getPathToClosestNaturalResource(conf.getProducerConf().rawMaterialConf, getEntryPointTile()));
        if (path) {
            auto miner(characterFactory.generateMiner(conf.getProducerConf().miner.conf, selfReference, path));
            miners.insert(miner.toStrongRef().get(), miner);
            minerGeneration.reset();
        }
        else {
            minerGeneration.postpone();
        }
    }
}



bool ProducerBuilding::canGenerateNewMiner() const
{
    if (miners.size() >= conf.getProducerConf().miner.maxSimultaneous) {
        return false;
    }

    auto expectedQuantity(rawMaterialStock + (miners.size() + 1) * conf.getProducerConf().miningQuantity);
    if (expectedQuantity > conf.getProducerConf().maxRawMaterialStock) {
        return false;
    }

    return true;
}



void ProducerBuilding::handleProduction()
{
    if (!deliveryMan) {
        deliveryMan = characterFactory.generateDeliveryMan(
            conf.getProducerConf().deliveryManConf,
            selfReference,
            conf.getProducerConf().producedItemConf,
            1
        );
        rawMaterialStock -= conf.getProducerConf().requiredQuantityForProduction;
        productionCountDown = PRODUCTION_INTERVAL;
        notifyViewDataChange();
    }
}
