#include "DynamicElementInformation.hpp"

#include <yaml-cpp/yaml.h>

#include "exceptions/BadConfigurationException.hpp"
#include "global/yamlLibraryEnhancement.hpp"
#include "defines.hpp"

DynamicElementInformation::DynamicElementInformation(QObject* parent, const QString& key, const YAML::Node& model) :
    QObject(parent),
    type(resolveType(model["type"].as<QString>())),
    key(key),
    title(model["title"] ? model["title"].as<QString>() : ""),
#ifdef SLOW_MOTION
    speed(model["speed"] ? model["speed"].as<qreal>() / CYCLE_PER_SECOND / 8.0 : 0.0),
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



const QString& DynamicElementInformation::getTitle() const
{
    return title;
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



void DynamicElementInformation::checkModel(const QString& key, const YAML::Node& model)
{
    if (!model["type"]) {
        throw BadConfigurationException("Missing \"type\" parameter in configuration for node \"" + key + "\".");
    }
}



DynamicElementInformation::Type DynamicElementInformation::resolveType(const QString& type)
{
    if (type == "targetedWalker") return Type::TargetedWalker;
    if (type == "randomWalker")   return Type::RandomWalker;

    throw BadConfigurationException("Unknown dynamic element of type \"" + type + "\"");
}
