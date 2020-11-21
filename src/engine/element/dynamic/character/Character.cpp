#include "Character.hpp"

#include "src/engine/element/dynamic/MotionHandler.hpp"
#include "src/engine/element/static/building/AbstractProcessableBuilding.hpp"
#include "src/engine/state/CharacterState.hpp"
#include "src/global/conf/CharacterInformation.hpp"



Character::Character(
    CharacterManagerInterface& characterManager,
    const PathGeneratorInterface& pathGenerator,
    const CharacterInformation& conf,
    const QSharedPointer<AbstractProcessableBuilding>& issuer
) :
    AbstractProcessable(),
    characterManager(characterManager),
    pathGenerator(pathGenerator),
    conf(conf),
    motionHandler(conf.getSpeed(), issuer->getEntryPoint()),
    issuer(issuer),
    stateVersion(0)
{

}



bool Character::isOfType(const CharacterInformation& conf) const
{
    return &conf == &this->conf;
}



const QWeakPointer<AbstractProcessableBuilding>& Character::getIssuer() const
{
    return issuer;
}



CharacterState Character::getCurrentState() const
{
    return { reinterpret_cast<qintptr>(this), conf, motionHandler.getCurrentLocation(), motionHandler.getCurrentDirection(), stateVersion };
}



void Character::process(const CycleDate& /*date*/)
{
    if (motionHandler.move()) {
        notifyViewDataChange();
    }
}



void Character::notifyViewDataChange()
{
    ++stateVersion;
}
