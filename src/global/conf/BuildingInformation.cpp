#include "BuildingInformation.hpp"

#include <yaml-cpp/yaml.h>

#include "src/exceptions/BadConfigurationException.hpp"
#include "src/global/conf/BehaviorInformation.hpp"
#include "src/global/conf/Conf.hpp"
#include "src/global/conf/BuildingSearchCriteriaDescription.hpp"
#include "src/global/yamlLibraryEnhancement.hpp"
#include "src/defines.hpp"



BuildingInformation::BuildingInformation(QObject* parent, const Conf* conf, const QString& key, const YAML::Node& model) :
    QObject(parent),
    type(resolveType(model["type"].as<QString>())),
    key(key),
    title(model["title"] ? model["title"].as<QString>() : ""),
    size(model["size"] ? model["size"].as<int>() : 1),
    price(model["price"] ? model["price"].as<int>() : 0),
    employees(model["employees"] ? model["employees"].as<int>() : 0),
    fireRiskIncrement(model["fireRisk"] ? model["fireRisk"].as<int>() : 0),
    damageRiskIncrement(model["damageRisk"] ? model["damageRisk"].as<int>() : 0),
    areaDescription(),
    behaviors(),
    image("assets/img/static/building/" + key + ".png")
{
    if (model["behaviors"]) {
        for (auto node : model["behaviors"]) {
            BehaviorInformation::checkModel(key, node);
            behaviors.append(new BehaviorInformation(this, conf, node));
        }
    }
}



void BuildingInformation::resolveDependencies(const Conf* conf)
{
    for (auto behavior : behaviors) {
        behavior->resolveDependencies(conf);
    }
}



BuildingInformation::Type BuildingInformation::getType() const
{
    return type;
}



const QString& BuildingInformation::getTitle() const
{
    return title;
}



const MapSize& BuildingInformation::getSize() const
{
    return size;
}



const QList<BehaviorInformation*>& BuildingInformation::getBehaviors() const
{
    return behaviors;
}



const QPixmap& BuildingInformation::getImage() const
{
    return image;
}



void BuildingInformation::checkModel(const QString& key, const YAML::Node& model)
{
    if (!model["type"]) {
        throw BadConfigurationException("Missing \"type\" parameter in configuration for node \"" + key + "\".");
    }
}



BuildingInformation::Type BuildingInformation::resolveType(const QString& type)
{
    if (type == "building")        return Type::Building;
    if (type == "cityEntryPoint")  return Type::CityEntryPoint;
    if (type == "road")            return Type::Road;

    throw BadConfigurationException("Unknown building of type \"" + type + "\".");
}
