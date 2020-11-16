#include "ImmigrantCharacter.hpp"

#include "src/engine/element/dynamic/CharacterManagerInterface.hpp"
#include "src/engine/element/static/building/AbstractProcessableBuilding.hpp"
#include "src/engine/map/path/PathGenerator.hpp"



ImmigrantCharacter::ImmigrantCharacter(
    CharacterManagerInterface& characterManager,
    const PathGeneratorInterface& pathGenerator,
    const CharacterInformation& conf,
    AbstractProcessableBuilding& issuer,
    AbstractProcessableBuilding& target
) :
    Character(characterManager, pathGenerator, conf, issuer),
    target(target.getReference<AbstractProcessableBuilding>())
{
    motionHandler.takePath(pathGenerator.generateShortestPathTo(issuer.getEntryPoint(), target.getEntryPoint()));
}



void ImmigrantCharacter::process(const CycleDate& date)
{
    Character::process(date);

    if (motionHandler.isPathCompleted()) {
        if (target.isValid()) {
            target.get().processInteraction(date, *this);
        }
        characterManager.clearCharacter(*this);
    }
}
