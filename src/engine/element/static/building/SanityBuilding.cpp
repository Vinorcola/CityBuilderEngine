#include "SanityBuilding.hpp"

#include "src/engine/element/dynamic/character/WanderingCharacter.hpp"
#include "src/engine/element/dynamic/CharacterFactoryInterface.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/pointer/SmartPointerUtils.hpp"



SanityBuilding::SanityBuilding(
    CharacterFactoryInterface& characterFactory,
    const BuildingInformation& conf,
    const MapArea& area,
    Direction orientation,
    const MapCoordinates& entryPoint
) :
    AbstractProcessableBuilding(conf, area, orientation, entryPoint),
    characterFactory(characterFactory),
    walkerGeneration(conf.getMaxWorkers(), conf.getSanityConf().walker.generationInterval),
    walker()
{

}



QSharedPointer<AbstractProcessableBuilding> SanityBuilding::Create(
    CharacterFactoryInterface& characterFactory,
    const BuildingInformation& conf,
    const MapArea& area,
    Direction orientation,
    const MapCoordinates& entryPoint
) {
    auto sanity(new SanityBuilding(characterFactory, conf, area, orientation, entryPoint));
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
