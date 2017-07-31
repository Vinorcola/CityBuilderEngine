#include "DynamicElementInformation.hpp"

#include "defines.hpp"
#include "exceptions/BadConfigurationException.hpp"

DynamicElementInformation::DynamicElementInformation(QObject* parent, const QString& key, YAML::Node model) :
    QObject(parent),
    type(resolveTypeFromKey(key)),
    key(key),
#ifdef SLOW_MOTION
    speed(model["speed"] ? model["speed"].as<qreal>() / CYCLE_PER_SECOND / 8 : 0.0),
#else
    speed(model["speed"] ? model["speed"].as<qreal>() / CYCLE_PER_SECOND : 0.0),
#endif
    walkingCredit(model["walkingCredit"] ? model["walkingCredit"].as<int>() : 0),
    image("assets/img/dynamic/" + key + "/character.png")
{

}



DynamicElementInformation::Type DynamicElementInformation::getType() const
{
    return type;
}



qreal DynamicElementInformation::getSpeed() const
{
    return speed;
}



int DynamicElementInformation::getWalkingCredit() const
{
    return walkingCredit;
}



const QPixmap& DynamicElementInformation::getImage() const
{
    return image;
}



DynamicElementInformation::Type DynamicElementInformation::resolveTypeFromKey(const QString& key)
{
    if (key == "immigrant")      return Type::Immigrant;
    if (key == "superintendent") return Type::Superintendent;

    throw BadConfigurationException("Unknown dynamic element key \"" + key + "\"");
}
