#include "MinerCharacter.hpp"

#include "src/engine/element/dynamic/CharacterManagerInterface.hpp"
#include "src/engine/element/static/building/AbstractProcessableBuilding.hpp"
#include "src/engine/element/static/natureElement/NatureElement.hpp"
#include "src/engine/map/path/PathGenerator.hpp"



MinerCharacter::MinerCharacter(
    CharacterManagerInterface& characterManager,
    const PathGeneratorInterface& pathGenerator,
    const CharacterInformation& conf,
    AbstractProcessableBuilding& issuer,
    owner<PathInterface*> path
) :
    Character(characterManager, pathGenerator, conf, issuer),
    goingHome(false)
{
    motionHandler.takePath(path);
}



void MinerCharacter::goHome()
{
    if (issuer.isValid()) {
        goingHome = true;
        motionHandler.takePath(pathGenerator.generateShortestPathTo(
            motionHandler.getCurrentLocation(),
            issuer.get().getEntryPoint()
        ));
    }
}



void MinerCharacter::process(const CycleDate& date)
{
    Character::process(date);

    if (motionHandler.isPathCompleted()) {
        if (goingHome) {
            if (issuer.isValid()) {
                issuer.get().processInteraction(date, *this);
            }
            characterManager.clearCharacter(*this);
        }
        else {
            // TODO: Interaction with nature element.
            goHome();
        }
    }
}
