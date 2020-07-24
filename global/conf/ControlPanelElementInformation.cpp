#include "ControlPanelElementInformation.hpp"

#include <yaml-cpp/yaml.h>

#include "exceptions/BadConfigurationException.hpp"
#include "global/conf/Conf.hpp"
#include "global/yamlLibraryEnhancement.hpp"



ControlPanelElementInformation::ControlPanelElementInformation(QObject* parent, Conf* conf, const YAML::Node& model) :
    QObject(parent),
    type(resolveType(model["type"].as<QString>())),
    title(model["title"].as<QString>()),
    staticElementConf(model["staticElement"] ? conf->getStaticElementConf(model["staticElement"].as<QString>()) : nullptr),
    children()
{
    if (model["content"]) {
        for (auto node : model["content"]) {
            ControlPanelElementInformation::checkModel(node);
            children.append(new ControlPanelElementInformation(this, conf, node));
        }
    }
}



ControlPanelElementInformation::Type ControlPanelElementInformation::getType() const
{
    return type;
}



const QString& ControlPanelElementInformation::getTitle() const
{
    return title;
}



const BuildingInformation*ControlPanelElementInformation::getStaticElementConf() const
{
    return staticElementConf;
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
