#include "NatureElementInformation.hpp"

#include <yaml-cpp/yaml.h>

#include "src/exceptions/BadConfigurationException.hpp"
#include "src/global/yamlLibraryEnhancement.hpp"



NatureElementInformation::NatureElementInformation(QObject* parent, const QString& key, const YAML::Node& model) :
    QObject(parent),
    type(resolveType(key)),
    key(key),
    title(model["title"].as<QString>()),
    traversable(model["traversable"].as<bool>()),
    image("assets/img/static/nature/" + key + ".png")
{

}



bool NatureElementInformation::isTraversable() const
{
    return traversable;
}



const QPixmap& NatureElementInformation::getImage() const
{
    return image;
}



void NatureElementInformation::checkModel(const QString& key, const YAML::Node& model)
{
    if (!model["title"]) {
        throw BadConfigurationException("Missing \"title\" parameter in configuration for node \"" + key + "\".");
    }
    if (!model["traversable"]) {
        throw BadConfigurationException("Missing \"traversable\" parameter in configuration for node \"" + key + "\".");
    }
}



NatureElementInformation::Type NatureElementInformation::resolveType(const QString& type)
{
    if (type == "copper") return Type::Copper;
    if (type == "silver") return Type::Silver;
    if (type == "wood")   return Type::Wood;

    throw BadConfigurationException("Unknown nature element of type \"" + type + "\".");
}
