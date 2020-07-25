#include "BehaviorInformation.hpp"

#include <yaml-cpp/yaml.h>

#include "exceptions/BadConfigurationException.hpp"
#include "global/conf/Conf.hpp"
#include "global/conf/BuildingSearchCriteriaDescription.hpp"
#include "global/yamlLibraryEnhancement.hpp"
#include "defines.hpp"



BehaviorInformation::BehaviorInformation(QObject* parent, const Conf* conf, const YAML::Node& model) :
    QObject(parent),
    type(resolveType(model["type"].as<QString>())),
    dependencyWalkerConf(model["dependencyWalker"] ? conf->getCharacterConf(model["dependencyWalker"].as<QString>()) : nullptr),
    walkerConf(model["walkerType"] ? conf->getCharacterConf(model["walkerType"].as<QString>()) : nullptr),
    walkerGenerationInterval(model["generationInterval"] ? model["generationInterval"].as<int>() * CYCLE_PER_SECOND : 0),
    minWalkerGenerationInterval(model["minGenerationInterval"] ? model["minGenerationInterval"].as<qreal>() * CYCLE_PER_SECOND : 0),
    maxWalkerGenerationInterval(model["maxGenerationInterval"] ? model["maxGenerationInterval"].as<int>() * CYCLE_PER_SECOND : 0),
    maxWalkers(model["maxWalkers"] ? model["maxWalkers"].as<int>() : 0),
    items(),
    targetSearchCriteriaDescription(model["targetSearchCriteria"] ?
        new BuildingSearchCriteriaDescription(this, model["targetSearchCriteria"]) :
        nullptr
    ),
    targetSearchCriteria()
{
    if (model["items"]) {
        for (auto node : model["items"]) {
            items.append(conf->getItemConf(node.as<QString>()));
        }
    }
}



void BehaviorInformation::resolveDependencies(const Conf* conf)
{
    if (targetSearchCriteriaDescription) {
        targetSearchCriteria.reset(
            new BuildingSearchCriteria(conf->getBuildingConf(targetSearchCriteriaDescription->getTargetKey()))
        );
    }
}



BehaviorInformation::Type BehaviorInformation::getType() const
{
    return type;
}



const CharacterInformation* BehaviorInformation::getDependencyWalkerConf() const
{
    return dependencyWalkerConf;
}



const CharacterInformation* BehaviorInformation::getWalkerConf() const
{
    return walkerConf;
}



int BehaviorInformation::getWalkerGenerationInterval() const
{
    return walkerGenerationInterval;
}



int BehaviorInformation::getMinWalkerGenerationInterval() const
{
    return minWalkerGenerationInterval;
}



int BehaviorInformation::getMaxWalkerGenerationInterval() const
{
    return maxWalkerGenerationInterval;
}



int BehaviorInformation::getMaxWalkers() const
{
    return maxWalkers;
}



const QList<const ItemInformation*>& BehaviorInformation::getItems() const
{
    return items;
}



const BuildingSearchCriteria* BehaviorInformation::getTargetSearchCriteria() const
{
    return targetSearchCriteria.data();
}



void BehaviorInformation::checkModel(const QString& key, const YAML::Node& model)
{
    if (!model["type"]) {
        throw BadConfigurationException("Missing \"type\" parameter in configuration for behavior in node \"" + key + "\".");
    }
}



BehaviorInformation::Type BehaviorInformation::resolveType(const QString& type)
{
    if (type == "conditionalRandomWalkerGenerator") return Type::ConditionalRandomWalkerGenerator;
    if (type == "inhabitantContainer")              return Type::InhabitantContainer;
    if (type == "itemStorage")                      return Type::ItemStorage;
    if (type == "queuedWalkerGenerator")            return Type::QueuedWalkerGenerator;
    if (type == "randomWalkerGenerator")            return Type::RandomWalkerGenerator;
    if (type == "targetedWalkerGenerator")          return Type::TargetedWalkerGenerator;

    throw BadConfigurationException("Unknown behavior of type \"" + type + "\".");
}
