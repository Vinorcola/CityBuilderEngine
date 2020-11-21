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
    const MapCoordinates& entryPoint
) :
    AbstractProcessableBuilding(conf, area, entryPoint),
    searchEngine(searchEngine),
    characterFactory(characterFactory),
    nextWalkerGenerationDate()
{

}



QSharedPointer<AbstractProcessableBuilding> SchoolBuilding::Create(
    const BuildingSearchEngine& searchEngine,
    CharacterFactoryInterface& characterFactory,
    const BuildingInformation& conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
) {
    auto school(new SchoolBuilding(searchEngine, characterFactory, conf, area, entryPoint));
    QSharedPointer<AbstractProcessableBuilding> pointer(school);
    school->selfReference = pointer;

    return pointer;
}



void SchoolBuilding::init(const CycleDate& date)
{
    setupNextWalkerGenerationDate(date);
}



void SchoolBuilding::process(const CycleDate& date)
{
    if (date < nextWalkerGenerationDate) {
        return;
    }

    auto target(searchEngine.findClosestBuilding(conf.getSchoolConf().targetLaboratory, getEntryPoint()));
    if (target) {
        characterFactory.generateStudent(conf.getSchoolConf().student.conf, selfReference, target->getSelfReference());
    }

    setupNextWalkerGenerationDate(date);
}



void SchoolBuilding::setupNextWalkerGenerationDate(const CycleDate& date)
{
    nextWalkerGenerationDate.reassign(date, conf.getSchoolConf().student.generationInterval);
}
