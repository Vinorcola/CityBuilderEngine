#include "StaticSearchCriteriaDescription.hpp"

#include <yaml-cpp/yaml.h>



StaticSearchCriteriaDescription::StaticSearchCriteriaDescription(QObject* parent, const YAML::Node& model) :
    QObject(parent),
    targetKey(model["type"] ? QString::fromStdString(model["type"].as<std::string>()) : "")
{

}



const QString& StaticSearchCriteriaDescription::getTargetKey() const
{
    return targetKey;
}
