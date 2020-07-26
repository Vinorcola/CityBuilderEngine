#include "CharacterInformation.hpp"

#include <yaml-cpp/yaml.h>

#include "src/exceptions/BadConfigurationException.hpp"
#include "src/global/yamlLibraryEnhancement.hpp"
#include "src/defines.hpp"

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
    wanderingCredits(model["wanderingCredits"] ? model["wanderingCredits"].as<int>() : 0),
    image("assets/img/dynamic/character/" + key + ".png")
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



int CharacterInformation::getWanderingCredits() const
{
    return wanderingCredits;
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

    throw BadConfigurationException("Unknown character of type \"" + type + "\"");
}
