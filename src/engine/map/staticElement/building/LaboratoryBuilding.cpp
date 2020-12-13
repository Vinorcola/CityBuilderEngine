#include "LaboratoryBuilding.hpp"

#include "src/engine/map/dynamicElement/character/Character.hpp"
#include "src/engine/map/dynamicElement/character/WanderingCharacter.hpp"
#include "src/engine/map/dynamicElement/CharacterGeneratorInterface.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/pointer/SmartPointerUtils.hpp"



LaboratoryBuilding::LaboratoryBuilding(
    CharacterGeneratorInterface& characterFactory,
    const BuildingInformation& conf,
    const MapArea& area,
    Direction orientation,
    const MapCoordinates& entryPoint
) :
    AbstractProcessableBuilding(conf, area, orientation, entryPoint),
    characterFactory(characterFactory),
    workingCountDown(0),
    scientistGeneration(conf.getMaxWorkers(), conf.getLaboratoryConf().emittedScientist.generationInterval),
    scientist()
{

}



QSharedPointer<AbstractProcessableBuilding> LaboratoryBuilding::Create(
    CharacterGeneratorInterface& characterFactory,
    const BuildingInformation& conf,
    const MapArea& area,
    Direction orientation,
    const MapCoordinates& entryPoint
) {
    auto laboratory(new LaboratoryBuilding(characterFactory, conf, area, orientation, entryPoint));
    QSharedPointer<AbstractProcessableBuilding> pointer(laboratory);
    laboratory->selfReference = pointer;

    return pointer;
}



void LaboratoryBuilding::process(const CycleDate& /*date*/)
{
    if (!isActive()) {
        return;
    }

    if (workingCountDown <= 0) {
        return;
    }
    --workingCountDown;
    if (workingCountDown == 0) {
        notifyViewDataChange();
        return;
    }

    scientistGeneration.process(getCurrentWorkerQuantity());
    if (scientistGeneration.isReadyToGenerateWalker()) {
        scientist = characterFactory.generateWanderingCharacter(conf.getLaboratoryConf().emittedScientist.conf, selfReference);
        scientistGeneration.reset();
    }
}



bool LaboratoryBuilding::processInteraction(const CycleDate& /*date*/, Character& actor)
{
    if (matches(scientist, actor)) {
        scientist.clear();

        return true;
    }

    if (actor.isOfType(conf.getLaboratoryConf().acceptedStudent)) {
        workingCountDown = conf.getLaboratoryConf().producingInterval;
        notifyViewDataChange();

        return true;
    }

    return false;
}



BuildingStatus LaboratoryBuilding::getCurrentStatus() const
{
    if (!isActive()) {
        return BuildingStatus::Inactive;
    }
    if (workingCountDown > 0) {
        return BuildingStatus::Working;
    }

    return BuildingStatus::Active;
}



bool LaboratoryBuilding::canGenerateNewWalker() const
{
    return scientist.isNull();
}
