#include "ImmigrantCharacter.hpp"

#include "src/engine/map/dynamicElement/CharacterDisposerInterface.hpp"
#include "src/engine/map/path/PathGenerator.hpp"
#include "src/engine/map/staticElement/building/AbstractProcessableBuilding.hpp"



ImmigrantCharacter::ImmigrantCharacter(
    CharacterDisposerInterface& characterManager,
    const PathGeneratorInterface& pathGenerator,
    const CharacterInformation& conf,
    const QSharedPointer<AbstractProcessableBuilding>& issuer,
    const QSharedPointer<AbstractProcessableBuilding>& target
) :
    Character(characterManager, pathGenerator, conf, issuer),
    target(target)
{
    motionHandler.takePath(pathGenerator.generateShortestPathTo(issuer->getEntryPoint(), target->getEntryPoint()));
}



void ImmigrantCharacter::process(const CycleDate& date)
{
    Character::process(date);

    if (motionHandler.isPathCompleted()) {
        auto target(this->target.toStrongRef());
        if (target) {
            target->processInteraction(date, *this);
        }
        characterManager.clearCharacter(*this);
    }
}
