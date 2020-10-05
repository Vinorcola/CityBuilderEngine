#include "MapEntryPoint.hpp"

#include <QtCore/QRandomGenerator>

#include "src/engine/element/dynamic/character/ImmigrantCharacter.hpp"
#include "src/engine/element/dynamic/CharacterFactoryInterface.hpp"



MapEntryPoint::MapEntryPoint(
    CharacterFactoryInterface& characterFactory,
    const MapCoordinates& location,
    const CharacterInformation& immigrantConf
) :
    characterFactory(characterFactory),
    location(location),
    immigrantConf(immigrantConf),
    nextImmigrantGenerationDate(),
    immigrantRequestQueue()
{

}



void MapEntryPoint::requestImmigrant(OnCharacterCreationCallback onImmigrantCreation)
{
    immigrantRequestQueue.append(onImmigrantCreation);
}



void MapEntryPoint::process(const CycleDate& date)
{
    if (immigrantRequestQueue.isEmpty()) {
        return;
    }

    if (date == nextImmigrantGenerationDate) {
        auto &immigrant(characterFactory.generateImmigrant(immigrantConf));
        immigrantRequestQueue.front()(immigrant); // Call onImmigrantCreation callback.
        immigrantRequestQueue.pop_front(); // Remove callback from queue.
        setupNextImmigrantGenerationDate(date);
    } else if (date > nextImmigrantGenerationDate) {
        setupNextImmigrantGenerationDate(date);
    }
}



void MapEntryPoint::setupNextImmigrantGenerationDate(const CycleDate& currentDate)
{
    if (immigrantRequestQueue.isEmpty()) {
        return;
    }

    if (nextImmigrantGenerationDate <= currentDate) {
        nextImmigrantGenerationDate.reassign(currentDate, QRandomGenerator::global()->bounded(1, 91));
    }
}
