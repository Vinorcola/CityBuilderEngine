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
    Character(parent, conf, issuer)
{
    motionHandler.takePath(pathGenerator.generateShortestPathTo(initialLocation, issuer.getEntryPoint()));
}
