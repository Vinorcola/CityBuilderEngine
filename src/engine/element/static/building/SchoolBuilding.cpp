#include "SchoolBuilding.hpp"

#include "src/engine/element/dynamic/CharacterFactoryInterface.hpp"
#include "src/engine/element/static/building/LaboratoryBuilding.hpp"
#include "src/engine/map/MapSearchEngine.hpp"
#include "src/global/conf/BuildingInformation.hpp"



SchoolBuilding::SchoolBuilding(
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

    auto target(searchEngine.getLaboratory(conf.getSchoolConf().targetLaboratory));
    if (target != nullptr) {
        characterFactory.generateStudent(conf.getSchoolConf().student.conf, *this, *target);
    }

    setupNextWalkerGenerationDate(date);
}



void SchoolBuilding::setupNextWalkerGenerationDate(const CycleDate& date)
{
    nextWalkerGenerationDate.reassign(date, conf.getSchoolConf().student.generationInterval);
}
