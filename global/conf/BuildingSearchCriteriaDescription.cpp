#include "BuildingSearchCriteriaDescription.hpp"

#include <yaml-cpp/yaml.h>



BuildingSearchCriteriaDescription::BuildingSearchCriteriaDescription(QObject* parent, const YAML::Node& model) :
    QObject(parent),
    targetKey(model["type"] ? QString::fromStdString(model["type"].as<std::string>()) : "")
{

}



const QString& BuildingSearchCriteriaDescription::getTargetKey() const
{
    return targetKey;
}
