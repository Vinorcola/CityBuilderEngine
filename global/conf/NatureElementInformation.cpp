#include "NatureElementInformation.hpp"

#include <yaml-cpp/yaml.h>

#include "exceptions/BadConfigurationException.hpp"
#include "global/yamlLibraryEnhancement.hpp"



NatureElementInformation::NatureElementInformation(QObject* parent, const QString& key, const YAML::Node& model) :
    QObject(parent),
    type(resolveType(key)),
    key(key),
    title(model["title"].as<QString>()),
    convertible(model["convertible"].as<bool>()),
    image("assets/img/static/nature/" + key + ".png")
{

}



void NatureElementInformation::checkModel(const QString& key, const YAML::Node& model)
{
    if (!model["title"]) {
        throw BadConfigurationException("Missing \"title\" parameter in configuration for node \"" + key + "\".");
    }
    if (!model["convertible"]) {
        throw BadConfigurationException("Missing \"convertible\" parameter in configuration for node \"" + key + "\".");
    }
}



NatureElementInformation::Type NatureElementInformation::resolveType(const QString& type)
{
    if (type == "copper") return Type::Copper;
    if (type == "silver") return Type::Silver;
    if (type == "wood")   return Type::Wood;

    throw BadConfigurationException("Unknown nature element of type \"" + type + "\".");
}
