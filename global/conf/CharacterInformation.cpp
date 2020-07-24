#include "CharacterInformation.hpp"

#include <yaml-cpp/yaml.h>

#include "exceptions/BadConfigurationException.hpp"
#include "global/yamlLibraryEnhancement.hpp"
#include "defines.hpp"

CharacterInformation::CharacterInformation(QObject* parent, const QString& key, const YAML::Node& model) :
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



CharacterInformation::Type CharacterInformation::getType() const
{
    return type;
}



const QString& CharacterInformation::getKey() const
{
    return key;
}



const QString& CharacterInformation::getTitle() const
{
    return title;
}



qreal CharacterInformation::getSpeed() const
{
    return speed;
}



int CharacterInformation::getWalkingCredit() const
{
    return walkingCredit;
}



const QPixmap& CharacterInformation::getImage() const
{
    return image;
}



void CharacterInformation::checkModel(const QString& key, const YAML::Node& model)
{
    if (!model["type"]) {
        throw BadConfigurationException("Missing \"type\" parameter in configuration for node \"" + key + "\".");
    }
}



CharacterInformation::Type CharacterInformation::resolveType(const QString& type)
{
    if (type == "targetedWalker") return Type::TargetedWalker;
    if (type == "randomWalker")   return Type::RandomWalker;

    throw BadConfigurationException("Unknown dynamic element of type \"" + type + "\"");
}
