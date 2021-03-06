#include "WanderingCharacter.hpp"

#include "src/engine/map/dynamicElement/CharacterDisposerInterface.hpp"
#include "src/engine/map/path/PathGenerator.hpp"
#include "src/engine/map/staticElement/building/AbstractProcessableBuilding.hpp"
#include "src/global/conf/CharacterInformation.hpp"



WanderingCharacter::WanderingCharacter(
    CharacterDisposerInterface& characterManager,
    const PathGeneratorInterface& pathGenerator,
    const CharacterInformation& conf,
    const QSharedPointer<AbstractProcessableBuilding>& issuer
) :
    Character(characterManager, pathGenerator, conf, issuer),
    goingHome(false)
{
    motionHandler.takePath(pathGenerator.generateWanderingPath(issuer->getEntryPointTile(), conf.getWanderingCredits()));
}



void WanderingCharacter::goHome()
{
    auto issuer(this->issuer.toStrongRef());
    if (issuer) {
        goingHome = true;
        motionHandler.takePath(pathGenerator.generateShortestRoadPathTo(
            motionHandler.getCurrentTile(),
            issuer->getEntryPointTile()
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
