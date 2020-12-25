#include "MinerCharacter.hpp"

#include <cassert>

#include "src/engine/map/dynamicElement/CharacterDisposerInterface.hpp"
#include "src/engine/map/path/PathGenerator.hpp"
#include "src/engine/map/staticElement/building/AbstractProcessableBuilding.hpp"
#include "src/engine/map/staticElement/natureElement/NatureElement.hpp"
#include "src/engine/map/staticElement/natureElement/NatureElementSearchEngine.hpp"
#include "src/exceptions/NotImplementedException.hpp"
#include "src/global/conf/CharacterInformation.hpp"



MinerCharacter::MinerCharacter(
    CharacterDisposerInterface& characterManager,
    const PathGeneratorInterface& pathGenerator,
    const NatureElementSearchEngine& searchEngine,
    const CharacterInformation& conf,
    const QSharedPointer<AbstractProcessableBuilding>& issuer,
    QSharedPointer<PathInterface> path
) :
    Character(characterManager, pathGenerator, conf, issuer),
    searchEngine(searchEngine),
    goingHome(false),
    workingCountDown(conf.getActionInterval())
{
    motionHandler.takePath(path);
}



void MinerCharacter::goHome()
{
    auto issuer(this->issuer.toStrongRef());
    if (issuer) {
        goingHome = true;
        motionHandler.takePath(pathGenerator.generateShortestPathTo(
            motionHandler.getCurrentTile(),
            issuer->getEntryPointTile()
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
            if (workingCountDown == conf.getActionInterval()) {
                // Begin to work.
                auto target(motionHandler.target().toStrongRef());
                if (target.isNull()) {
                    // TODO: Target has been destroyed, find another target.
                    throw NotImplementedException("Handling destroyed natural resource");
                }
                auto naturalResource(target.dynamicCast<NatureElement>());
                assert(!naturalResource.isNull());
                if (naturalResource->isBusy()) {
                    auto path(searchEngine.getPathToClosestNaturalResource(
                        naturalResource->getConf(),
                        motionHandler.getCurrentTile()
                    ));
                    if (path.isNull()) {
                        // TODO: No more resources available. Destroy the character.
                        throw NotImplementedException("Destroy character");
                    }
                    motionHandler.takePath(path);
                    return;
                }
                naturalResource->startInteraction();
            }
            --workingCountDown;
            // TODO: It may happen that the target has been destroyed while the miner is working. Maybe we should handle
            // that case too, reset the working count down and find another target.
            if (workingCountDown <= 0) {
                // End of work.
                auto target(motionHandler.target().toStrongRef());
                if (!target.isNull()) {
                    // For now, we ignore if the target has been destroyed.
                    auto naturalResource(target.dynamicCast<NatureElement>());
                    assert(!naturalResource.isNull());
                    naturalResource->endInteraction();
                }
                workingCountDown = conf.getActionInterval();
                goHome();
            }
        }
    }
}
