#include "ItemInformation.hpp"

#include <yaml-cpp/yaml.h>

#include "src/exceptions/BadConfigurationException.hpp"
#include "src/global/yamlLibraryEnhancement.hpp"



ItemInformation::ItemInformation(const QString& key, const YAML::Node& model) :
    key(key),
    title(model["title"] ? model["title"].as<QString>() : "")
{

}



bool ItemInformation::operator!=(const ItemInformation& other) const
{
    return this != &other;
}



const QString& ItemInformation::getKey() const
{
    return key;
}



const QString& ItemInformation::getTitle() const
{
    return title;
}



void ItemInformation::checkModel(const QString& key, const YAML::Node& model)
{
    if (!model["title"]) {
        throw BadConfigurationException("Missing \"title\" parameter in configuration for node \"" + key + "\".");
    }
}
