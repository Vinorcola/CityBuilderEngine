#include "ImmigrantCharacter.hpp"

#include "src/engine/element/dynamic/CharacterManagerInterface.hpp"
#include "src/engine/element/static/building/AbstractProcessableBuilding.hpp"
#include "src/engine/element/static/path/PathGenerator.hpp"



ImmigrantCharacter::ImmigrantCharacter(
    CharacterManagerInterface& characterManager,
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
