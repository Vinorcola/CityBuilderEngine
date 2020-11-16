#include "WanderingCharacter.hpp"

#include "src/engine/element/dynamic/CharacterManagerInterface.hpp"
#include "src/engine/element/static/building/AbstractProcessableBuilding.hpp"
#include "src/engine/map/path/PathGenerator.hpp"
#include "src/global/conf/CharacterInformation.hpp"



WanderingCharacter::WanderingCharacter(
    CharacterManagerInterface& characterManager,
    const PathGeneratorInterface& pathGenerator,
    const CharacterInformation& conf,
    AbstractProcessableBuilding& issuer
) :
    Character(characterManager, pathGenerator, conf, issuer),
    goingHome(false)
{
    motionHandler.takePath(pathGenerator.generateWanderingPath(issuer.getEntryPoint(), conf.getWanderingCredits()));
}



void WanderingCharacter::goHome()
{
    if (issuer.isValid()) {
        goingHome = true;
        motionHandler.takePath(pathGenerator.generateShortestRoadPathTo(
            motionHandler.getCurrentLocation(),
            issuer.get().getEntryPoint()
        ));
    }
}



void WanderingCharacter::process(const CycleDate& date)
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
            goHome();
        }
    }
}
