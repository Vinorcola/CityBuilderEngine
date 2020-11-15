#include "ImmigrantCharacter.hpp"

#include "src/engine/element/dynamic/CharacterManagerInterface.hpp"
#include "src/engine/element/static/building/ProcessableBuilding.hpp"
#include "src/engine/map/path/PathGenerator.hpp"



ImmigrantCharacter::ImmigrantCharacter(
    QObject* parent,
    CharacterManagerInterface& characterManager,
    const PathGeneratorInterface& pathGenerator,
    const CharacterInformation& conf,
    ProcessableBuilding& issuer,
    ProcessableBuilding& target
) :
    Character(parent, characterManager, pathGenerator, conf, issuer),
    target(&target)
{
    motionHandler.takePath(pathGenerator.generateShortestPathTo(issuer.getEntryPoint(), target.getEntryPoint()));
}



void ImmigrantCharacter::process(const CycleDate& date)
{
    Character::process(date);

    if (motionHandler.isPathCompleted()) {
        if (target) {
            target->processInteraction(date, *this);
        }
        characterManager.clearCharacter(*this);
    }
}
