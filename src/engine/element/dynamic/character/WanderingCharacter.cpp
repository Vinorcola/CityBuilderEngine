#include "WanderingCharacter.hpp"

#include "src/engine/element/dynamic/CharacterManagerInterface.hpp"
#include "src/engine/element/static/building/AbstractProcessableBuilding.hpp"
#include "src/engine/element/static/path/PathGenerator.hpp"
#include "src/global/conf/CharacterInformation.hpp"



WanderingCharacter::WanderingCharacter(
    CharacterManagerInterface& characterManager,
    const PathGeneratorInterface& pathGenerator,
    const CharacterInformation& conf,
    const QSharedPointer<AbstractProcessableBuilding>& issuer
) :
    Character(characterManager, pathGenerator, conf, issuer),
    goingHome(false)
{
    motionHandler.takePath(pathGenerator.generateWanderingPath(issuer->getEntryPoint(), conf.getWanderingCredits()));
}



void WanderingCharacter::goHome()
{
    auto issuer(this->issuer.toStrongRef());
    if (issuer) {
        goingHome = true;
        motionHandler.takePath(pathGenerator.generateShortestRoadPathTo(
            motionHandler.getCurrentLocation(),
            issuer->getEntryPoint()
        ));
    }
}



void WanderingCharacter::process(const CycleDate& date)
{
    Character::process(date);

    if (motionHandler.isPathCompleted()) {
        if (goingHome) {
            auto issuer(this->issuer.toStrongRef());
            if (issuer) {
                issuer->processInteraction(date, *this);
            }
            characterManager.clearCharacter(*this);
        }
        else {
            goHome();
        }
    }
}
