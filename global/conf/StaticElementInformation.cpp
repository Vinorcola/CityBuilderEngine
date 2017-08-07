#include "StaticElementInformation.hpp"

#include <yaml-cpp/yaml.h>

#include "exceptions/BadConfigurationException.hpp"
#include "global/conf/Conf.hpp"
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
    image("assets/img/static/" + key + "/building.png"),
    randomWalkerConf(model["randomWalkerType"] ?
        conf->getDynamicElementConf(QString::fromStdString(model["randomWalkerType"].as<std::string>())) :
        nullptr
    ),
    randomWalkerInterval((model["randomWalkerInterval"] ? model["randomWalkerInterval"].as<int>() : 0) * CYCLE_PER_SECOND),
    maxNumberOfRandomWalkers(model["maxRandomWalkers"] ? model["maxRandomWalkers"].as<int>() : 0),
    targetedWalkerConf(model["targetedWalkerType"] ?
        conf->getDynamicElementConf(QString::fromStdString(model["targetedWalkerType"].as<std::string>())) :
        nullptr
    ),
    targetedWalkerInterval((model["targetedWalkerInterval"] ? model["targetedWalkerInterval"].as<int>() : 0) * CYCLE_PER_SECOND),
    targetCriteriaDescription(model["targetCriteria"] ?
        new StaticSearchCriteriaDescription(this, model["targetCriteria"]) :
        nullptr
    ),
    targetCriteria()
{

}



void StaticElementInformation::resolveDependencies(const Conf* conf)
{
    if (targetCriteriaDescription) {
        targetCriteria.reset(new StaticSearchCriteria(conf->getStaticElementConf(targetCriteriaDescription->getTargetKey())));
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



const QPixmap& StaticElementInformation::getImage() const
{
    return image;
}



const DynamicElementInformation* StaticElementInformation::getRandomWalkerConf() const
{
    return randomWalkerConf;
}



int StaticElementInformation::getRandomWalkerGenerationInterval() const
{
    return randomWalkerInterval;
}



int StaticElementInformation::getMaxNumberOfRandomWalkers() const
{
    return maxNumberOfRandomWalkers;
}



const DynamicElementInformation* StaticElementInformation::getTargetedWalkerConf() const
{
    return targetedWalkerConf;
}



int StaticElementInformation::getTargetedWalkerGenerationInterval() const
{
    return targetedWalkerInterval;
}



const StaticSearchCriteria& StaticElementInformation::getTargetCriteria() const
{
return *targetCriteria;
}



void StaticElementInformation::checkModel(const QString& key, const YAML::Node& model)
{
    if (!model["type"]) {
        throw BadConfigurationException("Missing \"type\" parameter in configuration for node \"" + key + "\".");
    }
}



StaticElementInformation::Type StaticElementInformation::resolveType(const QString& type)
{
    if (type == "cityEntryPoint")  return Type::CityEntryPoint;
    if (type == "cultureBuilding") return Type::CultureBuilding;
    if (type == "housingBuilding") return Type::HousingBuilding;
    if (type == "serviceBuilding") return Type::ServiceBuilding;
    if (type == "road")            return Type::Road;

    throw BadConfigurationException("Unknown static element of type \"" + type + "\".");
}
