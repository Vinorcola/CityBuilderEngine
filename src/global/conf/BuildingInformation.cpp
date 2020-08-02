#include "BuildingInformation.hpp"

#include <yaml-cpp/yaml.h>

#include "src/exceptions/BadConfigurationException.hpp"
#include "src/exceptions/UnexpectedException.hpp"
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
    producer(nullptr)
{
    switch (type) {
        case Type::Producer:
            producer = new Producer(model);
            break;
    }
}



BuildingInformation::~BuildingInformation()
{
    if (producer) {
        delete producer;
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



const BuildingInformation::Producer& BuildingInformation::getProducerConf() const
{
    if (producer == nullptr) {
        throw UnexpectedException("This building conf does not have producer information.");
    }

    return *producer;
}



const QPixmap& BuildingInformation::getImage() const
{
    return graphics.image;
}



BuildingInformation::Type BuildingInformation::resolveType(const QString& type)
{
    if (type == "producer") return Type::Producer;
    if (type == "road")     return Type::Road;

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



BuildingInformation::WalkerGeneration::WalkerGeneration(
    const CharacterInformation& conf,
    const int generationInterval,
    const int maxSimultaneous
) :
    conf(conf),
    generationInterval(generationInterval),
    maxSimultaneous(maxSimultaneous)
{

}



BuildingInformation::Producer::Producer(const ModelReader& model) :
    producedItemConf(model.getItemConf("producedItem")),
    rawMaterialConf(model.getNatureElementConf("rawMaterialItem")),
    miner(
        model.getCharacterConf("minerCharacter"),
        model.getOptionalInt("minerGenerationInterval", 4) * CYCLE_PER_SECOND,
        model.getOptionalInt("maxSimultaneousMiners", 2)
    ),
    miningQuantity(model.getOptionalInt("miningQuantity", 25)),
    rawMaterialQuantityToProduce(model.getOptionalInt("rawMaterialQuantityToProduce", 100)),
    maxStoredRawMaterialQuantity(model.getOptionalInt("maxStoredRawMaterialQuantity", 500))
{

}
