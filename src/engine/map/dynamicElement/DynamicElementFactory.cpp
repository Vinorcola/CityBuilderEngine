#include "DynamicElementFactory.hpp"

#include "src/engine/map/dynamicElement/character/DeliveryManCharacter.hpp"
#include "src/engine/map/dynamicElement/character/ImmigrantCharacter.hpp"
#include "src/engine/map/dynamicElement/character/MinerCharacter.hpp"
#include "src/engine/map/dynamicElement/character/StudentCharacter.hpp"
#include "src/engine/map/dynamicElement/character/WanderingCharacter.hpp"
#include "src/engine/map/path/PathGeneratorInterface.hpp"
#include "src/engine/map/staticElement/building/AbstractProcessableBuilding.hpp"



DynamicElementFactory::DynamicElementFactory(
    CharacterDisposerInterface& characterDisposer,
    const PathGeneratorInterface& pathGenerator,
    const BuildingSearchEngine& buildingSearchEngine
) :
    characterDisposer(characterDisposer),
    pathGenerator(pathGenerator),
    buildingSearchEngine(buildingSearchEngine)
{

}



QSharedPointer<Character> DynamicElementFactory::generateDeliveryMan(
    const CharacterInformation& conf,
    QSharedPointer<AbstractProcessableBuilding> issuer,
    const ItemInformation& transportedItemConf,
    const int transportedQuantity
) {
    return QSharedPointer<Character>(new DeliveryManCharacter(
        characterDisposer,
        pathGenerator,
        buildingSearchEngine,
        conf,
        issuer,
        transportedItemConf,
        transportedQuantity
    ));
}



QSharedPointer<Character> DynamicElementFactory::generateImmigrant(
    const CharacterInformation& conf,
    QSharedPointer<AbstractProcessableBuilding> issuer,
    QSharedPointer<AbstractProcessableBuilding> target
) {
    return QSharedPointer<Character>(new ImmigrantCharacter(characterDisposer, pathGenerator, conf, issuer, target));
}



QSharedPointer<Character> DynamicElementFactory::generateMiner(
    const CharacterInformation& conf,
    QSharedPointer<AbstractProcessableBuilding> issuer,
    QSharedPointer<PathInterface> path
) {
    return QSharedPointer<Character>(new MinerCharacter(characterDisposer, pathGenerator, conf, issuer, path));
}



QSharedPointer<Character> DynamicElementFactory::generateStudent(
    const CharacterInformation& conf,
    QSharedPointer<AbstractProcessableBuilding> issuer,
    QSharedPointer<AbstractProcessableBuilding> target
) {
    return QSharedPointer<Character>(new StudentCharacter(
        characterDisposer,
        pathGenerator,
        conf,
        issuer,
        target,
        pathGenerator.generateShortestRoadPathTo(issuer->getEntryPointTile(), target->getEntryPointTile())
    ));
}



QSharedPointer<Character> DynamicElementFactory::generateWanderingCharacter(
    const CharacterInformation& conf,
    QSharedPointer<AbstractProcessableBuilding> issuer
) {
    return QSharedPointer<Character>(new WanderingCharacter(characterDisposer, pathGenerator, conf, issuer));
}
