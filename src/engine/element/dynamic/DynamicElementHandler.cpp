#include "DynamicElementHandler.hpp"

#include <QtCore/QtAlgorithms>

#include "src/engine/element/dynamic/character/DeliveryManCharacter.hpp"
#include "src/engine/element/dynamic/character/ImmigrantCharacter.hpp"
#include "src/engine/element/dynamic/character/MinerCharacter.hpp"
#include "src/engine/element/dynamic/character/StudentCharacter.hpp"
#include "src/engine/element/dynamic/character/WanderingCharacter.hpp"
#include "src/engine/element/dynamic/PathGeneratorInterface.hpp"
#include "src/engine/state/CharacterState.hpp"



DynamicElementHandler::DynamicElementHandler(
    const PathGeneratorInterface& pathGenerator,
    const BuildingSearchEngine& buildingSearchEngine
) :
    pathGenerator(pathGenerator),
    buildingSearchEngine(buildingSearchEngine),
    currentState()
{

}



DynamicElementHandler::~DynamicElementHandler()
{
    qDeleteAll(currentState.characters);
}



DeliveryManCharacter& DynamicElementHandler::generateDeliveryMan(
    const CharacterInformation& conf,
    AbstractProcessableBuilding& issuer,
    const ItemInformation& transportedItemConf,
    const int transportedQuantity
) {
    auto character(new DeliveryManCharacter(
        *this,
        pathGenerator,
        buildingSearchEngine,
        conf,
        issuer,
        transportedItemConf,
        transportedQuantity
    ));
    currentState.characters.push_back(character);

    return *character;
}



ImmigrantCharacter& DynamicElementHandler::generateImmigrant(
    const CharacterInformation& conf,
    AbstractProcessableBuilding& issuer,
    AbstractProcessableBuilding& target
) {
    auto character(new ImmigrantCharacter(*this, pathGenerator, conf, issuer, target));
    currentState.characters.push_back(character);

    return *character;
}



MinerCharacter& DynamicElementHandler::generateMiner(
    const CharacterInformation& conf,
    AbstractProcessableBuilding& issuer,
    owner<PathInterface*> path
) {
    auto character(new MinerCharacter(*this, pathGenerator, conf, issuer, path));
    currentState.characters.push_back(character);

    return *character;
}



StudentCharacter& DynamicElementHandler::generateStudent(
    const CharacterInformation& conf,
    AbstractProcessableBuilding& issuer,
    AbstractProcessableBuilding& target
) {
    auto path(pathGenerator.generateShortestRoadPathTo(issuer.getEntryPoint(), target.getEntryPoint()));
    auto character(new StudentCharacter(*this, pathGenerator, conf, issuer, target, path));
    currentState.characters.push_back(character);

    return *character;
}



WanderingCharacter& DynamicElementHandler::generateWanderingCharacter(
    const CharacterInformation& conf,
    AbstractProcessableBuilding& issuer
) {
    auto character(new WanderingCharacter(*this, pathGenerator, conf, issuer));
    currentState.characters.push_back(character);

    return *character;
}



void DynamicElementHandler::clearCharacter(Character& character)
{
    currentState.characters.remove(&character);
    delete &character;
}



QList<CharacterState> DynamicElementHandler::getCharactersState() const
{
    QList<CharacterState> list;
    for (auto element : currentState.characters) {
        list.append(element->getCurrentState());
    }

    return list;
}
