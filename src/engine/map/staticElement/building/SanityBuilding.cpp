#include "SanityBuilding.hpp"

#include "src/engine/map/dynamicElement/character/WanderingCharacter.hpp"
#include "src/engine/map/dynamicElement/CharacterGeneratorInterface.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/pointer/SmartPointerUtils.hpp"



SanityBuilding::SanityBuilding(
    CharacterGeneratorInterface& characterFactory,
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const Tile& entryPointTile
) :
    AbstractProcessableBuilding(conf, area, orientation, entryPointTile),
    characterFactory(characterFactory),
    walkerGeneration(conf.getMaxWorkers(), conf.getSanityConf().walker.generationInterval),
    walker()
{

}



QSharedPointer<AbstractProcessableBuilding> SanityBuilding::Create(
    CharacterGeneratorInterface& characterFactory,
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const Tile& entryPointTile
) {
    auto sanity(new SanityBuilding(characterFactory, conf, area, orientation, entryPointTile));
    QSharedPointer<AbstractProcessableBuilding> pointer(sanity);
    sanity->selfReference = pointer;

    return pointer;
}



void SanityBuilding::process(const CycleDate& /*date*/)
{
    if (!isActive()) {
        return;
    }

    if (!canGenerateNewWalker()) {
        return;
    }

    walkerGeneration.process(getCurrentWorkerQuantity());
    if (walkerGeneration.isReadyToGenerateWalker()) {
        walker = characterFactory.generateWanderingCharacter(conf.getSanityConf().walker.conf, selfReference);
        walkerGeneration.reset();
    }
}



bool SanityBuilding::processInteraction(const CycleDate& /*date*/, Character& actor)
{
    if (matches(walker, actor)) {
        walker.clear();

        return true;
    }

    return false;
}



bool SanityBuilding::canGenerateNewWalker() const
{
    return walker.isNull();
}
