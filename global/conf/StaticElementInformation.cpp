#include "StaticElementInformation.hpp"

#include "exceptions/BadConfigurationException.hpp"





StaticElementInformation::StaticElementInformation(const QString& key, YAML::Node model) :
    type(resolveKeyToType(key)),
    key(key),
    price(model[0].as<int>()),
    requiredEmployees(model[1].as<int>()),
    fireRiskIncrement(model[2].as<int>()),
    damageRiskIncrement(model[3].as<int>()),
    areaDescription()
{

}





StaticElementInformation::Type StaticElementInformation::getType() const
{
    return type;
}





StaticElementInformation::Type StaticElementInformation::resolveKeyToType(const QString& key)
{
    if      (key == "road")        return Type::Road;
    else if (key == "maintenance") return Type::Maintenance;

    throw BadConfigurationException("Unknown static element key \"" + key + "\"");
}
