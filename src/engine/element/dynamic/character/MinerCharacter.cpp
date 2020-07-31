#include "MinerCharacter.hpp"

#include "src/engine/element/static/NatureElement.hpp"



MinerCharacter::MinerCharacter(
    QObject* parent,
    const CharacterInformation& conf,
    ProcessableBuilding& issuer,
    owner<PathInterface*> path
) :
    Character(parent, conf, issuer)
{
    motionHandler.takePath(path);
}



void MinerCharacter::goHome(owner<PathInterface*> path)
{
    motionHandler.takePath(path);
}



void MinerCharacter::process(const CycleDate& date)
{
    Character::process(date);

    if (motionHandler.isPathCompleted()) {
        // TODO: Interaction with nature element.
        emit hasFinishedHarvest();
    }
}
