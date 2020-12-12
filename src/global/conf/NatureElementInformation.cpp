#include "NatureElementInformation.hpp"

#include <yaml-cpp/yaml.h>

#include "src/exceptions/BadConfigurationException.hpp"
#include "src/global/yamlLibraryEnhancement.hpp"



NatureElementInformation::NatureElementInformation(
    const QString& configDirectoryPath,
    const QString& key,
    const YAML::Node& model
) :
    type(resolveType(key)),
    key(key),
    title(model["title"].as<QString>()),
    traversable(model["traversable"].as<bool>()),
    imagePath(configDirectoryPath + "/images/static/nature/" + key + ".png")
{

}



const QString& NatureElementInformation::getTitle() const
{
    return title;
}



bool NatureElementInformation::isTraversable() const
{
    return traversable;
}



const QString& NatureElementInformation::getImagePath() const
{
    return imagePath;
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
    if (type == "grass")  return Type::Grass;
    if (type == "silver") return Type::Silver;
    if (type == "wood")   return Type::Wood;

    throw BadConfigurationException("Unknown nature element of type \"" + type + "\".");
}
