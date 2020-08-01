#include "Character.hpp"

#include "src/engine/element/dynamic/MotionHandler.hpp"
#include "src/engine/element/static/ProcessableBuilding.hpp"
#include "src/global/conf/CharacterInformation.hpp"



Character::Character(
    QObject* parent,
    const CharacterInformation& conf,
    ProcessableBuilding& issuer
) :
    QObject(parent),
    AbstractProcessable(),
    conf(conf),
    motionHandler(conf.getSpeed(), issuer.getEntryPoint()),
    issuer(&issuer)
{

}



const CharacterInformation& Character::getConf() const
{
    return conf;
}



const MapCoordinates& Character::getCurrentLocation() const
{
    return motionHandler.getCurrentLocation();
}



optional<ProcessableBuilding*> Character::getIssuer() const
{
    return issuer;
}



void Character::process(const CycleDate& /*date*/)
{
    motionHandler.move();
}
