#include "DynamicElementHandler.hpp"

#include <QtCore/QtAlgorithms>

#include "src/engine/element/dynamic/character/DeliveryManCharacter.hpp"
#include "src/engine/element/dynamic/character/ImmigrantCharacter.hpp"
#include "src/engine/element/dynamic/character/MinerCharacter.hpp"
#include "src/engine/element/dynamic/character/StudentCharacter.hpp"
#include "src/engine/element/dynamic/character/WanderingCharacter.hpp"
#include "src/engine/element/dynamic/PathGeneratorInterface.hpp"
#include "src/engine/element/static/building/AbstractProcessableBuilding.hpp"
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



QWeakPointer<Character> DynamicElementHandler::generateDeliveryMan(
    const CharacterInformation& conf,
    QSharedPointer<AbstractProcessableBuilding> issuer,
    const ItemInformation& transportedItemConf,
    const int transportedQuantity
) {
    QSharedPointer<Character> character(new DeliveryManCharacter(
        *this,
        pathGenerator,
        buildingSearchEngine,
        conf,
        issuer,
        transportedItemConf,
        transportedQuantity
    ));
    currentState.characters.insert(character.get(), character);

    return character;
}



QWeakPointer<Character> DynamicElementHandler::generateImmigrant(
    const CharacterInformation& conf,
    QSharedPointer<AbstractProcessableBuilding> issuer,
    QSharedPointer<AbstractProcessableBuilding> target
) {
    QSharedPointer<Character> character(new ImmigrantCharacter(*this, pathGenerator, conf, issuer, target));
    currentState.characters.insert(character.get(), character);

    return character;
}



QWeakPointer<Character> DynamicElementHandler::generateMiner(
    const CharacterInformation& conf,
    QSharedPointer<AbstractProcessableBuilding> issuer,
    owner<PathInterface*> path
) {
    QSharedPointer<Character> character(new MinerCharacter(*this, pathGenerator, conf, issuer, path));
    currentState.characters.insert(character.get(), character);

    return character;
}



QWeakPointer<Character> DynamicElementHandler::generateStudent(
    const CharacterInformation& conf,
    QSharedPointer<AbstractProcessableBuilding> issuer,
    QSharedPointer<AbstractProcessableBuilding> target
) {
    auto path(pathGenerator.generateShortestRoadPathTo(issuer->getEntryPoint(), target->getEntryPoint()));
    QSharedPointer<Character> character(new StudentCharacter(*this, pathGenerator, conf, issuer, target, path));
    currentState.characters.insert(character.get(), character);

    return character;
}



QWeakPointer<Character> DynamicElementHandler::generateWanderingCharacter(
    const CharacterInformation& conf,
    QSharedPointer<AbstractProcessableBuilding> issuer
) {
    QSharedPointer<Character> character(new WanderingCharacter(*this, pathGenerator, conf, issuer));
    currentState.characters.insert(character.get(), character);

    return character;
}



void DynamicElementHandler::clearCharacter(Character& character)
{
    currentState.characters.remove(&character);
}



QList<CharacterState> DynamicElementHandler::getCharactersState() const
{
    QList<CharacterState> list;
    for (auto element : currentState.characters) {
        list.append(element->getCurrentState());
    }

    return list;
}
