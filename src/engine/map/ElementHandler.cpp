#include "ElementHandler.hpp"

#include <QDebug>

#include "src/engine/element/dynamic/character/MinerCharacter.hpp"
#include "src/engine/element/static/building/ProducerBuilding.hpp"
#include "src/engine/element/static/NatureElement.hpp"
#include "src/engine/map/Map.hpp"
#include "src/engine/map/MapArea.hpp"
#include "src/exceptions/UnexpectedException.hpp"
#include "src/global/conf/BuildingInformation.hpp"



ElementHandler::ElementHandler(const Map& map, const MapSearchEngine& searchEngine, const PathGenerator& pathGenerator) :
    QObject(),
    BuildingFactoryInterface(),
    CharacterFactoryInterface(),
    map(map),
    searchEngine(searchEngine),
    pathGenerator(pathGenerator),
    buildings(),
    characters(),
    natureElements()
{

}



const std::list<Building*>& ElementHandler::getBuildings() const
{
    return buildings;
}



ProducerBuilding& ElementHandler::generateProducer(
    const BuildingInformation& conf,
    const MapArea& area
) {
    auto entryPoint(map.getBestEntryPoint(area));
    auto building(new ProducerBuilding(this, searchEngine, *this, conf, area, entryPoint));
    buildings.push_back(building);

    emit buildingCreated(*building);

    return *building;
}



const std::list<Character*>& ElementHandler::getCharacters() const
{
    return characters;
}



MinerCharacter& ElementHandler::generateMiner(
    const CharacterInformation& conf,
    ProcessableBuilding& issuer,
    owner<PathInterface*> path
) {
    auto character(new MinerCharacter(this, pathGenerator, conf, issuer, path));
    characters.push_back(character);

    emit characterCreated(*character);

    return *character;
}



const std::list<NatureElement*>& ElementHandler::getNatureElements() const
{
    return natureElements;
}



NatureElement& ElementHandler::generateNatureElement(const NatureElementInformation& conf, const MapArea& area)
{
    auto natureElement(new NatureElement(this, conf, area));
    natureElements.push_back(natureElement);

    emit natureElementCreated(*natureElement);

    return *natureElement;
}



void ElementHandler::canConstructBuilding(const BuildingInformation& conf, const MapArea& area)
{
    if (!map.isValidArea(area)) {
        throw UnexpectedException("Try to create a building on an invalid area: " + area.toString() + ".");
    }
    if (area.getSize() != conf.getSize()) {
        throw UnexpectedException("Try to build a building on a area not matching the configured size.");
    }
    if (!map.isFreeArea(area)) {
        qDebug() << "WARNING: Try to create a building on an occupyed area " + area.toString() + ". Skiping the creation.";
        return;
    }
}
