#include "StudentCharacter.hpp"

#include "src/engine/element/dynamic/CharacterManagerInterface.hpp"
#include "src/engine/element/static/building/ProcessableBuilding.hpp"



StudentCharacter::StudentCharacter(
    QObject* parent,
    CharacterManagerInterface& characterManager,
    const PathGeneratorInterface& pathGenerator,
    const CharacterInformation& conf,
    ProcessableBuilding& issuer,
    ProcessableBuilding& target,
    owner<PathInterface*> path
) :
    Character(parent, characterManager, pathGenerator, conf, issuer),
    target(&target)
{
    motionHandler.takePath(path);
}



void StudentCharacter::process(const CycleDate& date)
{
    Character::process(date);

    if (motionHandler.isPathCompleted()) {
        if (target) {
            target->processInteraction(date, *this);
        }
        characterManager.clearCharacter(*this);
    }
}
