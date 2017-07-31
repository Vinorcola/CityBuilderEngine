#include "StaticElementInformation.hpp"

#include "exceptions/BadConfigurationException.hpp"



StaticElementInformation::StaticElementInformation(QObject* parent, const QString& key, YAML::Node model) :
    QObject(parent),
    type(resolveTypeFromKey(key)),
    key(key),
    size(model["size"] ? model["size"].as<int>() : 1),
    price(model["price"] ? model["price"].as<int>() : 0),
    employees(model["employees"] ? model["employees"].as<int>() : 0),
    fireRiskIncrement(model["fireRisk"] ? model["fireRisk"].as<int>() : 0),
    damageRiskIncrement(model["damageRisk"] ? model["damageRisk"].as<int>() : 0),
    areaDescription(),
    image("assets/img/static/" + key + "/building.png")
{

}



StaticElementInformation::Type StaticElementInformation::getType() const
{
    return type;
}



const MapSize& StaticElementInformation::getSize() const
{
    return size;
}



const QPixmap& StaticElementInformation::getImage() const
{
    return image;
}



StaticElementInformation::Type StaticElementInformation::resolveTypeFromKey(const QString& key)
{
    if (key == "cityEntryPoint") return Type::CityEntryPoint;
    if (key == "house")          return Type::House;
    if (key == "maintenance")    return Type::Maintenance;
    if (key == "road")           return Type::Road;

    throw BadConfigurationException("Unknown static element key \"" + key + "\"");
}
