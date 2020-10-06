#include "StudentCharacter.hpp"

#include "src/engine/element/static/ProcessableBuilding.hpp"



StudentCharacter::StudentCharacter(
    QObject* parent,
    const PathGenerator& pathGenerator,
    const CharacterInformation& conf,
    ProcessableBuilding& issuer,
    ProcessableBuilding& target,
    owner<PathInterface*> path
) :
    Character(parent, conf, issuer, issuer.getEntryPoint()),
    pathGenerator(pathGenerator),
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
        } else {
            // TODO: Destroy the character.
        }
    }
}
