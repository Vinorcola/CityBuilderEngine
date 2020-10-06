#include "MinerCharacter.hpp"

#include "src/engine/element/static/NatureElement.hpp"
#include "src/engine/element/static/ProcessableBuilding.hpp"
#include "src/engine/map/path/PathGenerator.hpp"



MinerCharacter::MinerCharacter(
    QObject* parent,
    const PathGenerator& pathGenerator,
    const CharacterInformation& conf,
    ProcessableBuilding& issuer,
    owner<PathInterface*> path
) :
    Character(parent, conf, issuer, issuer.getEntryPoint()),
    pathGenerator(pathGenerator),
    goingHome(false)
{
    motionHandler.takePath(path);
}



void MinerCharacter::goHome()
{
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
            if (issuer) {
                issuer->processInteraction(date, *this);
            }
        }
        else {
            // TODO: Interaction with nature element.
            emit hasFinishedHarvest();
        }
    }
}
