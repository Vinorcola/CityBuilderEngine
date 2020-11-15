#include "StudentCharacter.hpp"

#include "src/engine/element/dynamic/CharacterManagerInterface.hpp"
#include "src/engine/element/static/building/AbstractProcessableBuilding.hpp"



StudentCharacter::StudentCharacter(
    QObject* parent,
    CharacterManagerInterface& characterManager,
    const PathGeneratorInterface& pathGenerator,
    const CharacterInformation& conf,
    AbstractProcessableBuilding& issuer,
    AbstractProcessableBuilding& target,
    owner<PathInterface*> path
) :
    Character(parent, characterManager, pathGenerator, conf, issuer),
    target(target.getReference<AbstractProcessableBuilding>())
{
    motionHandler.takePath(path);
}



void StudentCharacter::process(const CycleDate& date)
{
    Character::process(date);

    if (motionHandler.isPathCompleted()) {
        if (target.isValid()) {
            target.get().processInteraction(date, *this);
        }
        characterManager.clearCharacter(*this);
    }
}
