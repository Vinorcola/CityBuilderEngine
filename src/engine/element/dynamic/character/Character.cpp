#include "Character.hpp"

#include "src/engine/element/dynamic/MotionHandler.hpp"
#include "src/engine/element/static/building/ProcessableBuilding.hpp"
#include "src/global/conf/CharacterInformation.hpp"



Character::Character(
    QObject* parent,
    CharacterManagerInterface& characterManager,
    const PathGeneratorInterface& pathGenerator,
    const CharacterInformation& conf,
    ProcessableBuilding& issuer
) :
    QObject(parent),
    AbstractProcessable(),
    characterManager(characterManager),
    pathGenerator(pathGenerator),
    conf(conf),
    motionHandler(conf.getSpeed(), issuer.getEntryPoint()),
    issuer(&issuer),
    viewVersion(0)
{

}



bool Character::isOfType(const CharacterInformation& conf) const
{
    return &conf == &this->conf;
}



const CharacterInformation& Character::getConf() const
{
    return conf;
}



const MapCoordinates& Character::getCurrentLocation() const
{
    return motionHandler.getCurrentLocation();
}



Direction Character::getCurrentDirection() const
{
    return motionHandler.getCurrentDirection();
}



optional<ProcessableBuilding*> Character::getIssuer() const
{
    return issuer;
}



bool Character::isViewUpToDate(const int currentViewVersion) const
{
    return currentViewVersion == viewVersion;
}



int Character::getViewVersion() const
{
    return viewVersion;
}



void Character::process(const CycleDate& /*date*/)
{
    if (motionHandler.move()) {
        notifyViewDataChange();
    }
}



void Character::notifyViewDataChange()
{
    ++viewVersion;
}
