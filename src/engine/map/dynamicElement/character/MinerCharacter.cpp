#include "MinerCharacter.hpp"

#include "src/engine/map/dynamicElement/CharacterDisposerInterface.hpp"
#include "src/engine/map/path/PathGenerator.hpp"
#include "src/engine/map/staticElement/building/AbstractProcessableBuilding.hpp"
#include "src/engine/map/staticElement/natureElement/NatureElement.hpp"



MinerCharacter::MinerCharacter(
    CharacterDisposerInterface& characterManager,
    const PathGeneratorInterface& pathGenerator,
    const CharacterInformation& conf,
    const QSharedPointer<AbstractProcessableBuilding>& issuer,
    QSharedPointer<PathInterface> path
) :
    Character(characterManager, pathGenerator, conf, issuer),
    goingHome(false)
{
    motionHandler.takePath(path);
}



void MinerCharacter::goHome()
{
    auto issuer(this->issuer.toStrongRef());
    if (issuer) {
        goingHome = true;
        motionHandler.takePath(pathGenerator.generateShortestPathTo(
            motionHandler.getCurrentLocation(),
            issuer->getEntryPoint()
        ));
    }
}



void MinerCharacter::process(const CycleDate& date)
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
            // TODO: Interaction with nature element.
            goHome();
        }
    }
}
