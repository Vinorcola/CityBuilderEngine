#include "SchoolBuilding.hpp"

#include "src/engine/map/dynamicElement/CharacterGeneratorInterface.hpp"
#include "src/engine/map/staticElement/building/BuildingSearchEngine.hpp"
#include "src/engine/map/staticElement/building/LaboratoryBuilding.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/geometry/DynamicElementCoordinates.hpp"



SchoolBuilding::SchoolBuilding(
    const BuildingSearchEngine& searchEngine,
    CharacterGeneratorInterface& characterFactory,
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const TileCoordinates& entryPoint
) :
    AbstractProcessableBuilding(conf, area, orientation, entryPoint),
    searchEngine(searchEngine),
    characterFactory(characterFactory),
    walkerGeneration(conf.getMaxWorkers(), conf.getSchoolConf().student.generationInterval)
{

}



QSharedPointer<AbstractProcessableBuilding> SchoolBuilding::Create(
    const BuildingSearchEngine& searchEngine,
    CharacterGeneratorInterface& characterFactory,
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const TileCoordinates& entryPoint
) {
    auto school(new SchoolBuilding(searchEngine, characterFactory, conf, area, orientation, entryPoint));
    QSharedPointer<AbstractProcessableBuilding> pointer(school);
    school->selfReference = pointer;

    return pointer;
}



void SchoolBuilding::process(const CycleDate& /*date*/)
{
    if (!isActive()) {
        return;
    }

    walkerGeneration.process(getCurrentWorkerQuantity());
    if (walkerGeneration.isReadyToGenerateWalker()) {
        auto target(searchEngine.findClosestBuilding(conf.getSchoolConf().targetLaboratory, getEntryPoint().toDynamicElementCoordinates()));
        if (target) {
            characterFactory.generateStudent(conf.getSchoolConf().student.conf, selfReference, target);
            walkerGeneration.reset();
        }
        else {
            walkerGeneration.postpone();
        }
    }
}
