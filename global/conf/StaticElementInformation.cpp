#include "StaticElementInformation.hpp"

#include "exceptions/BadConfigurationException.hpp"
#include "global/conf/Conf.hpp"



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
    walkerConf(model["walkerType"] ? conf->getDynamicElementConf(QString::fromStdString(model["walkerType"].as<std::string>())) : nullptr)
{

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



const DynamicElementInformation* StaticElementInformation::getWalkerConf() const
{
    return walkerConf;
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
    if (type == "housingBuilding") return Type::HousingBuilding;
    if (type == "serviceBuilding") return Type::ServiceBuilding;
    if (type == "road")            return Type::Road;

    throw BadConfigurationException("Unknown static element of type \"" + type + "\".");
}
