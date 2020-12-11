#include "SchoolBuilding.hpp"

#include "src/engine/element/dynamic/CharacterFactoryInterface.hpp"
#include "src/engine/element/static/building/BuildingSearchEngine.hpp"
#include "src/engine/element/static/building/LaboratoryBuilding.hpp"
#include "src/global/conf/BuildingInformation.hpp"



SchoolBuilding::SchoolBuilding(
    const BuildingSearchEngine& searchEngine,
    CharacterFactoryInterface& characterFactory,
    const BuildingInformation& conf,
    const MapArea& area,
    Direction orientation,
    const MapCoordinates& entryPoint
) :
    AbstractProcessableBuilding(conf, area, orientation, entryPoint),
    searchEngine(searchEngine),
    characterFactory(characterFactory),
    walkerGeneration(conf.getMaxWorkers(), conf.getSchoolConf().student.generationInterval)
{

}



QSharedPointer<AbstractProcessableBuilding> SchoolBuilding::Create(
    const BuildingSearchEngine& searchEngine,
    CharacterFactoryInterface& characterFactory,
    const BuildingInformation& conf,
    const MapArea& area,
    Direction orientation,
    const MapCoordinates& entryPoint
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
        auto target(searchEngine.findClosestBuilding(conf.getSchoolConf().targetLaboratory, getEntryPoint()));
        if (target) {
            characterFactory.generateStudent(conf.getSchoolConf().student.conf, selfReference, target);
            walkerGeneration.reset();
        }
        else {
            walkerGeneration.postpone();
        }
    }
}
