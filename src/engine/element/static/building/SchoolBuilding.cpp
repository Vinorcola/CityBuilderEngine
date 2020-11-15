#include "SchoolBuilding.hpp"

#include "src/engine/element/dynamic/CharacterFactoryInterface.hpp"
#include "src/engine/element/static/building/BuildingSearchEngine.hpp"
#include "src/engine/element/static/building/LaboratoryBuilding.hpp"
#include "src/global/conf/BuildingInformation.hpp"



SchoolBuilding::SchoolBuilding(
    QObject* parent,
    const BuildingSearchEngine& searchEngine,
    CharacterFactoryInterface& characterFactory,
    const BuildingInformation& conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
) :
    ProcessableBuilding(parent, conf, area, entryPoint),
    searchEngine(searchEngine),
    characterFactory(characterFactory),
    nextWalkerGenerationDate()
{

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
    if (target != nullptr) {
        characterFactory.generateStudent(conf.getSchoolConf().student.conf, *this, *target);
    }

    setupNextWalkerGenerationDate(date);
}



void SchoolBuilding::setupNextWalkerGenerationDate(const CycleDate& date)
{
    nextWalkerGenerationDate.reassign(date, conf.getSchoolConf().student.generationInterval);
}
