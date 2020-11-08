#include "ElementHandler.hpp"

#include <QDebug>

#include "src/engine/element/dynamic/character/DeliveryManCharacter.hpp"
#include "src/engine/element/dynamic/character/ImmigrantCharacter.hpp"
#include "src/engine/element/dynamic/character/MinerCharacter.hpp"
#include "src/engine/element/dynamic/character/StudentCharacter.hpp"
#include "src/engine/element/dynamic/character/WanderingCharacter.hpp"
#include "src/engine/element/static/building/FarmBuilding.hpp"
#include "src/engine/element/static/building/HouseBuilding.hpp"
#include "src/engine/element/static/building/LaboratoryBuilding.hpp"
#include "src/engine/element/static/building/ProducerBuilding.hpp"
#include "src/engine/element/static/building/Road.hpp"
#include "src/engine/element/static/building/SanityBuilding.hpp"
#include "src/engine/element/static/building/SchoolBuilding.hpp"
#include "src/engine/element/static/building/StorageBuilding.hpp"
#include "src/engine/element/static/NatureElement.hpp"
#include "src/engine/map/Map.hpp"
#include "src/engine/map/MapArea.hpp"
#include "src/engine/map/MapSearchEngine.hpp"
#include "src/exceptions/UnexpectedException.hpp"
#include "src/global/conf/BuildingInformation.hpp"



ElementHandler::ElementHandler(Map& map, MapSearchEngine& searchEngine, const PathGenerator& pathGenerator) :
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



const std::list<QSharedPointer<Building>>& ElementHandler::getBuildings() const
{
    return buildings;
}



FarmBuilding& ElementHandler::generateFarm(const BuildingInformation& conf, const MapArea& area)
{
    auto entryPoint(map.getBestEntryPoint(area));
    QSharedPointer<FarmBuilding> building(new FarmBuilding(this, *this, conf, area, entryPoint));
    buildings.push_back(building);

    emit buildingCreated(building);

    return *building;
}



HouseBuilding& ElementHandler::generateHouse(const BuildingInformation& conf, const MapArea& area)
{
    auto entryPoint(map.getBestEntryPoint(area));
    QSharedPointer<HouseBuilding> building(new HouseBuilding(this, map.getImmigrantGenerator(), conf, area, entryPoint));
    buildings.push_back(building);

    emit buildingCreated(building);

    return *building;
}



LaboratoryBuilding& ElementHandler::generateLaboratory(const BuildingInformation& conf, const MapArea& area)
{
    auto entryPoint(map.getBestEntryPoint(area));
    QSharedPointer<LaboratoryBuilding> building(new LaboratoryBuilding(this, *this, conf, area, entryPoint));
    buildings.push_back(building);
    searchEngine.registerLaboratoryBuilding(*building);

    emit buildingCreated(building);

    return *building;
}



ProducerBuilding& ElementHandler::generateProducer(const BuildingInformation& conf, const MapArea& area)
{
    auto entryPoint(map.getBestEntryPoint(area));
    QSharedPointer<ProducerBuilding> building(new ProducerBuilding(this, searchEngine, *this, conf, area, entryPoint));
    buildings.push_back(building);

    emit buildingCreated(building);

    return *building;
}



SanityBuilding& ElementHandler::generateSanity(const BuildingInformation& conf, const MapArea& area)
{
    auto entryPoint(map.getBestEntryPoint(area));
    QSharedPointer<SanityBuilding> building(new SanityBuilding(this, *this, conf, area, entryPoint));
    buildings.push_back(building);

    emit buildingCreated(building);

    return *building;
}



SchoolBuilding& ElementHandler::generateSchool(const BuildingInformation& conf, const MapArea& area)
{
    auto entryPoint(map.getBestEntryPoint(area));
    QSharedPointer<SchoolBuilding> building(new SchoolBuilding(this, searchEngine, *this, conf, area, entryPoint));
    buildings.push_back(building);

    emit buildingCreated(building);

    return *building;
}



StorageBuilding& ElementHandler::generateStorage(const BuildingInformation& conf, const MapArea& area)
{
    auto entryPoint(map.getBestEntryPoint(area));
    QSharedPointer<StorageBuilding> building(new StorageBuilding(this, conf, area, entryPoint));
    buildings.push_back(building);
    searchEngine.registerStorageBuilding(*building);

    emit buildingCreated(building);

    return *building;
}



Road& ElementHandler::generateRoad(const BuildingInformation& conf, const MapCoordinates& location)
{
    QSharedPointer<Road> road(new Road(this, conf, location));
    buildings.push_back(road);

    emit buildingCreated(road);

    return *road;
}



const std::list<QSharedPointer<Character>>& ElementHandler::getCharacters() const
{
    return characters;
}



DeliveryManCharacter& ElementHandler::generateDeliveryMan(
    const CharacterInformation& conf,
    ProcessableBuilding& issuer,
    const ItemInformation& transportedItemConf,
    const int transportedQuantity
) {
    QSharedPointer<DeliveryManCharacter> character(
        new DeliveryManCharacter(this, *this, pathGenerator, searchEngine, conf, issuer, transportedItemConf, transportedQuantity)
    );
    characters.push_back(character);

    emit characterCreated(character);

    return *character;
}



ImmigrantCharacter& ElementHandler::generateImmigrant(
    const CharacterInformation& conf,
    ProcessableBuilding& issuer,
    ProcessableBuilding& target
) {
    QSharedPointer<ImmigrantCharacter> character(new ImmigrantCharacter(this, *this, pathGenerator, conf, issuer, target));
    characters.push_back(character);

    emit characterCreated(character);

    return *character;
}



MinerCharacter& ElementHandler::generateMiner(
    const CharacterInformation& conf,
    ProcessableBuilding& issuer,
    owner<PathInterface*> path
) {
    QSharedPointer<MinerCharacter> character(new MinerCharacter(this, *this, pathGenerator, conf, issuer, path));
    characters.push_back(character);

    emit characterCreated(character);

    return *character;
}



StudentCharacter& ElementHandler::generateStudent(
    const CharacterInformation& conf,
    ProcessableBuilding& issuer,
    ProcessableBuilding& target
) {
    auto path(pathGenerator.generateShortestRoadPathTo(issuer.getEntryPoint(), target.getEntryPoint()));
    QSharedPointer<StudentCharacter> character(new StudentCharacter(this, *this, pathGenerator, conf, issuer, target, path));
    characters.push_back(character);

    emit characterCreated(character);

    return *character;
}



WanderingCharacter& ElementHandler::generateWanderingCharacter(
    const CharacterInformation& conf,
    ProcessableBuilding& issuer
) {
    QSharedPointer<WanderingCharacter> character(new WanderingCharacter(this, *this, pathGenerator, conf, issuer));
    characters.push_back(character);

    emit characterCreated(character);

    return *character;
}



void ElementHandler::clearCharacter(Character& character)
{
    for (auto iterator(characters.begin()); iterator != characters.end(); ++iterator) {
        if (iterator->get() == &character) {
            characters.erase(iterator);
            return;
        }
    }
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
    if (!map.isConstructible(area)) {
        qDebug() << "WARNING: Try to create a building on an occupyed area " + area.toString() + ". Skiping the creation.";
        return;
    }
}
