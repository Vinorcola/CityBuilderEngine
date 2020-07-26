#include "ItemInformation.hpp"

#include <yaml-cpp/yaml.h>

#include "src/exceptions/BadConfigurationException.hpp"
#include "src/global/yamlLibraryEnhancement.hpp"



ItemInformation::ItemInformation(QObject* parent, const QString& key, const YAML::Node& model) :
    QObject(parent),
    key(key),
    title(model["title"] ? model["title"].as<QString>() : "")
{

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
