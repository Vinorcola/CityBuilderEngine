#include "StaticElementInformation.hpp"

#include <yaml-cpp/yaml.h>

#include "exceptions/BadConfigurationException.hpp"
#include "global/conf/BehaviorInformation.hpp"
#include "global/conf/Conf.hpp"
#include "global/conf/StaticSearchCriteriaDescription.hpp"
#include "defines.hpp"



StaticElementInformation::StaticElementInformation(QObject* parent, const Conf* conf, const QString& key, const YAML::Node& model) :
    QObject(parent),
    type(resolveType(QString::fromStdString(model["type"].as<std::string>()))),
    key(key),
    title(model["title"] ? QString::fromStdString(model["title"].as<std::string>()) : ""),
    size(model["size"] ? model["size"].as<int>() : 1),
    price(model["price"] ? model["price"].as<int>() : 0),
    employees(model["employees"] ? model["employees"].as<int>() : 0),
    fireRiskIncrement(model["fireRisk"] ? model["fireRisk"].as<int>() : 0),
    damageRiskIncrement(model["damageRisk"] ? model["damageRisk"].as<int>() : 0),
    areaDescription(),
    behaviors(),
    image("assets/img/static/" + key + "/building.png")
{
    if (model["behaviors"]) {
        for (auto node : model["behaviors"]) {
            BehaviorInformation::checkModel(key, node);
            behaviors.append(new BehaviorInformation(this, conf, node));
        }
    }
}



void StaticElementInformation::resolveDependencies(const Conf* conf)
{
    for (auto behavior : behaviors) {
        behavior->resolveDependencies(conf);
    }
}



StaticElementInformation::Type StaticElementInformation::getType() const
{
    return type;
}



const QString& StaticElementInformation::getTitle() const
{
    return title;
}



const MapSize& StaticElementInformation::getSize() const
{
    return size;
}



const QList<BehaviorInformation*>& StaticElementInformation::getBehaviors() const
{
    return behaviors;
}



const QPixmap& StaticElementInformation::getImage() const
{
    return image;
}



void StaticElementInformation::checkModel(const QString& key, const YAML::Node& model)
{
    if (!model["type"]) {
        throw BadConfigurationException("Missing \"type\" parameter in configuration for node \"" + key + "\".");
    }
}



StaticElementInformation::Type StaticElementInformation::resolveType(const QString& type)
{
    if (type == "building")        return Type::Building;
    if (type == "cityEntryPoint")  return Type::CityEntryPoint;
    if (type == "road")            return Type::Road;

    throw BadConfigurationException("Unknown static element of type \"" + type + "\".");
}
