#include "WanderingCharacter.hpp"

#include "src/engine/element/static/ProcessableBuilding.hpp"
#include "src/engine/map/path/PathGenerator.hpp"
#include "src/global/conf/CharacterInformation.hpp"



WanderingCharacter::WanderingCharacter(
    QObject* parent,
    const PathGenerator& pathGenerator,
    const CharacterInformation& conf,
    ProcessableBuilding& issuer
) :
    Character(parent, conf, issuer, issuer.getEntryPoint()),
    pathGenerator(pathGenerator),
    goingHome(false)
{
    motionHandler.takePath(pathGenerator.generateWanderingPath(issuer.getEntryPoint(), conf.getWanderingCredits()));
}



void WanderingCharacter::goHome()
{
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
            if (issuer) {
                issuer->processInteraction(date, *this);
            }
        }
        else {
            goHome();
        }
    }
}
