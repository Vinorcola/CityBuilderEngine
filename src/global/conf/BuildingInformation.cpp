#include "BuildingInformation.hpp"

#include <yaml-cpp/yaml.h>

#include "src/exceptions/BadConfigurationException.hpp"
#include "src/global/conf/BehaviorInformation.hpp"
#include "src/global/conf/Conf.hpp"
#include "src/global/conf/BuildingSearchCriteriaDescription.hpp"
#include "src/global/conf/ModelReader.hpp"
#include "src/global/yamlLibraryEnhancement.hpp"
#include "src/defines.hpp"



BuildingInformation::BuildingInformation(QObject* parent, const Conf* conf, const ModelReader& model) :
    QObject(parent),
    key(model.getKey()),
    type(resolveType(model.getString("type"))),
    common(model),
    graphics(model),
    behaviors()
{
    if (model.getNode()["behaviors"]) {
        for (auto node : model.getNode()["behaviors"]) {
            BehaviorInformation::checkModel(model.getKey(), node);
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
    return common.title;
}



const MapSize& BuildingInformation::getSize() const
{
    return common.size;
}



const QList<BehaviorInformation*>& BuildingInformation::getBehaviors() const
{
    return behaviors;
}



const QPixmap& BuildingInformation::getImage() const
{
    return graphics.image;
}



BuildingInformation::Type BuildingInformation::resolveType(const QString& type)
{
    if (type == "building")        return Type::Building;
    if (type == "cityEntryPoint")  return Type::CityEntryPoint;
    if (type == "road")            return Type::Road;

    throw BadConfigurationException("Unknown building of type \"" + type + "\".");
}



BuildingInformation::Common::Common(const ModelReader& model) :
    title(model.getString("title")),
    size(model.getOptionalInt("size", 1)),
    price(model.getOptionalInt("price")),
    employees(model.getOptionalInt("employees")),
    fireRiskIncrement(model.getOptionalInt("fireRisk")),
    damageRiskIncrement(model.getOptionalInt("damageRisk"))
{

}



BuildingInformation::Graphics::Graphics(const ModelReader& model) :
    image("assets/img/static/building/" + model.getKey() + ".png")
{

}
