#include "DynamicElementRegistry.hpp"

#include <cassert>

#include "src/engine/map/dynamicElement/character/Character.hpp"
#include "src/engine/map/dynamicElement/DynamicElementFactory.hpp"



DynamicElementRegistry::DynamicElementRegistry(
    const PathGeneratorInterface& pathGenerator,
    const BuildingSearchEngine& buildingSearchEngine
) :
    factory(*this, pathGenerator, buildingSearchEngine),
    characters(),
    waitingForRegistrationList(),
    waitingForUnregistrationList()
{

}



QWeakPointer<Character> DynamicElementRegistry::generateDeliveryMan(
    const CharacterInformation& conf,
    QSharedPointer<AbstractProcessableBuilding> issuer,
    const ItemInformation& transportedItemConf,
    const int transportedQuantity
) {
    auto character(factory.generateDeliveryMan(conf, issuer, transportedItemConf, transportedQuantity));
    assert(!character.isNull());
    waitingForRegistrationList.append(character);

    return character;
}



QWeakPointer<Character> DynamicElementRegistry::generateImmigrant(
    const CharacterInformation& conf,
    QSharedPointer<AbstractProcessableBuilding> issuer,
    QSharedPointer<AbstractProcessableBuilding> target
) {
    auto character(factory.generateImmigrant(conf, issuer, target));
    assert(!character.isNull());
    waitingForRegistrationList.append(character);

    return character;
}



QWeakPointer<Character> DynamicElementRegistry::generateMiner(
    const CharacterInformation& conf,
    QSharedPointer<AbstractProcessableBuilding> issuer,
    QSharedPointer<PathInterface> path
) {
    auto character(factory.generateMiner(conf, issuer, path));
    assert(!character.isNull());
    waitingForRegistrationList.append(character);

    return character;
}



QWeakPointer<Character> DynamicElementRegistry::generateStudent(
    const CharacterInformation& conf,
    QSharedPointer<AbstractProcessableBuilding> issuer,
    QSharedPointer<AbstractProcessableBuilding> target
) {
    auto character(factory.generateStudent(conf, issuer, target));
    assert(!character.isNull());
    waitingForRegistrationList.append(character);

    return character;
}



QWeakPointer<Character> DynamicElementRegistry::generateWanderingCharacter(
    const CharacterInformation& conf,
    QSharedPointer<AbstractProcessableBuilding> issuer
) {
    auto character(factory.generateWanderingCharacter(conf, issuer));
    assert(!character.isNull());
    waitingForRegistrationList.append(character);

    return character;
}



void DynamicElementRegistry::clearCharacter(Character& character)
{
    waitingForUnregistrationList.append(&character);
}



void DynamicElementRegistry::process(const CycleDate& date)
{
    // Note: The order below is important: current, unregistration and finally registration.

    // Process current character list.
    for (auto character : characters) {
        character->process(date);
    }

    // Process unregistration.
    for (auto characterToRemove : waitingForUnregistrationList) {
        characters.remove(characterToRemove);
    }
    waitingForUnregistrationList.clear();

    // Process registration.
    for (auto& newCharacter : waitingForRegistrationList) {
        characters.insert(newCharacter.get(), newCharacter);
    }
    waitingForRegistrationList.clear();
}
