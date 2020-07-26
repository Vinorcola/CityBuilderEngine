#include "BuildingSearchCriteriaDescription.hpp"

#include <yaml-cpp/yaml.h>

#include "src/global/yamlLibraryEnhancement.hpp"



BuildingSearchCriteriaDescription::BuildingSearchCriteriaDescription(QObject* parent, const YAML::Node& model) :
    QObject(parent),
    targetKey(model["type"] ? model["type"].as<QString>() : "")
{

}



const QString& BuildingSearchCriteriaDescription::getTargetKey() const
{
    return targetKey;
}
