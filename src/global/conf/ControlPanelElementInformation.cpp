#include "ControlPanelElementInformation.hpp"

#include <yaml-cpp/yaml.h>

#include "src/exceptions/BadConfigurationException.hpp"
#include "src/exceptions/UnexpectedException.hpp"
#include "src/global/conf/Conf.hpp"
#include "src/global/yamlLibraryEnhancement.hpp"



ControlPanelElementInformation::ControlPanelElementInformation(Conf& conf, const YAML::Node& model) :
    type(resolveType(model["type"].as<QString>())),
    title(model["title"].as<QString>()),
    staticElementConf(model["building"] ? &conf.getBuildingConf(model["building"].as<QString>()) : nullptr),
    children()
{
    if (model["content"]) {
        for (auto node : model["content"]) {
            ControlPanelElementInformation::checkModel(node);
            children.append(new ControlPanelElementInformation(conf, node));
        }
    }
}



ControlPanelElementInformation::~ControlPanelElementInformation()
{
    qDeleteAll(children);
}



ControlPanelElementInformation::Type ControlPanelElementInformation::getType() const
{
    return type;
}



const QString& ControlPanelElementInformation::getTitle() const
{
    return title;
}



const BuildingInformation& ControlPanelElementInformation::getStaticElementConf() const
{
    if (!staticElementConf) {
        throw UnexpectedException("This building conf does not have house information.");
    }

    return *staticElementConf;
}



const QList<ControlPanelElementInformation*>& ControlPanelElementInformation::getChildren() const
{
    return children;
}



void ControlPanelElementInformation::checkModel(const YAML::Node& model)
{
    if (!model["type"]) {
        throw BadConfigurationException("Missing \"type\" parameter in configuration for control panel element.");
    }
    if (!model["title"]) {
        throw BadConfigurationException("Missing \"title\" parameter in configuration for control panel element.");
    }
}



ControlPanelElementInformation::Type ControlPanelElementInformation::resolveType(const QString& type)
{
    if (type == "button") return Type::Button;
    if (type == "panel")  return Type::Panel;

    throw BadConfigurationException("Unknown control panel element of type \"" + type + "\"");
}
