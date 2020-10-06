#include "ImmigrantCharacter.hpp"

#include "src/engine/element/static/ProcessableBuilding.hpp"
#include "src/engine/map/path/PathGenerator.hpp"



ImmigrantCharacter::ImmigrantCharacter(
    QObject* parent,
    const PathGenerator& pathGenerator,
    const CharacterInformation& conf,
    const MapCoordinates& initialLocation,
    ProcessableBuilding& issuer
) :
    Character(parent, conf, issuer, initialLocation)
{
    motionHandler.takePath(pathGenerator.generateShortestPathTo(initialLocation, issuer.getEntryPoint()));
}



void ImmigrantCharacter::process(const CycleDate& date)
{
    Character::process(date);

    if (motionHandler.isPathCompleted()) {
        if (issuer) {
            issuer->processInteraction(date, *this);
        } else {
            // TODO: Destroy the character.
        }
    }
}
