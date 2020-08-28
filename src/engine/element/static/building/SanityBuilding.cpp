#include "SanityBuilding.hpp"

#include "src/engine/element/dynamic/character/WanderingCharacter.hpp"
#include "src/engine/element/dynamic/CharacterFactoryInterface.hpp"
#include "src/global/conf/BuildingInformation.hpp"



SanityBuilding::SanityBuilding(
    QObject* parent,
    CharacterFactoryInterface& characterFactory,
    const BuildingInformation& conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
) :
    ProcessableBuilding(parent, conf, area, entryPoint),
    characterFactory(characterFactory),
    walker(),
    nextWalkerGenerationDate()
{

}



void SanityBuilding::init(const CycleDate& date)
{
    setupNextWalkerGenerationDate(date);
}



void SanityBuilding::process(const CycleDate& date)
{
    if (nextWalkerGenerationDate) {
        if (date < nextWalkerGenerationDate) {
            return;
        }

        walker = &characterFactory.generateWanderingCharacter(conf.getSanityConf().walker.conf, *this);

        if (canGenerateNewWalker()) {
            setupNextWalkerGenerationDate(date);
        }
        else {
            nextWalkerGenerationDate.reset();
        }
    }
    else if (canGenerateNewWalker()) {
        setupNextWalkerGenerationDate(date);
    }
}



bool SanityBuilding::processInteraction(const CycleDate& date, Character& actor)
{
    if (&actor == walker) {
        characterFactory.clearCharacter(actor);
        walker.clear();

        return true;
    }

    return false;
}



bool SanityBuilding::canGenerateNewWalker() const
{
    return walker.isNull();
}



void SanityBuilding::setupNextWalkerGenerationDate(const CycleDate& date)
{
    nextWalkerGenerationDate.reassign(date, conf.getSanityConf().walker.generationInterval);
}
