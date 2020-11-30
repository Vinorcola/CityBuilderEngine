#include "BuildingInformation.hpp"

#include <yaml-cpp/yaml.h>

#include "src/exceptions/BadConfigurationException.hpp"
#include "src/exceptions/UnexpectedException.hpp"
#include "src/global/conf/BuildingAreaPartDescription.hpp"
#include "src/global/conf/ImageSequenceInformation.hpp"
#include "src/global/conf/ModelReader.hpp"
#include "src/global/yamlLibraryEnhancement.hpp"
#include "src/defines.hpp"



BuildingInformation::BuildingInformation(const ModelReader& model) :
    key(model.getKey()),
    type(resolveType(model.getString("type"))),
    common(model),
    graphics(),
    farm(nullptr),
    house(nullptr),
    producer(nullptr),
    sanity(nullptr),
    school(nullptr),
    storage(nullptr)
{
    QString basePath("assets/img/static/building/" + key + "/");
    QString manifestPath(basePath + "manifest.yaml");
    YAML::Node manifestRoot(YAML::LoadFile(manifestPath.toStdString()));

    graphics.mainImagePath = basePath + manifestRoot["building"]["mainImage"].as<QString>();
    if (manifestRoot["building"]["animation"]) {
        QString animationPath(basePath + "animation/");
        for (auto imageNode : manifestRoot["building"]["animation"]) {
            graphics.activeAnimation.append(new ImageSequenceInformation(
                animationPath + imageNode["file"].as<QString>(),
                imageNode["position"].as<QPoint>()
            ));
        }
    }
}



BuildingInformation::~BuildingInformation()
{
    if (farm) {
        delete farm;
    }
    if (house) {
        delete house;
    }
    if (laboratory) {
        delete laboratory;
    }
    if (producer) {
        delete producer;
    }
    if (sanity) {
        delete sanity;
    }
    if (school) {
        delete school;
    }
    if (storage) {
        delete storage;
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



int BuildingInformation::getMaxWorkers() const
{
    return common.maxWorkers;
}



const BuildingInformation::Graphics& BuildingInformation::getGraphicsData() const
{
    return graphics;
}



const BuildingInformation::Farm& BuildingInformation::getFarmConf() const
{
    if (farm == nullptr) {
        throw UnexpectedException("This building conf does not have farm information.");
    }

    return *farm;
}



const BuildingInformation::House& BuildingInformation::getHouseConf() const
{
    if (house == nullptr) {
        throw UnexpectedException("This building conf does not have house information.");
    }

    return *house;
}



const BuildingInformation::Laboratory& BuildingInformation::getLaboratoryConf() const
{
    if (laboratory == nullptr) {
        throw UnexpectedException("This building conf does not have laboratory information.");
    }

    return *laboratory;
}



const BuildingInformation::Producer& BuildingInformation::getProducerConf() const
{
    if (producer == nullptr) {
        throw UnexpectedException("This building conf does not have producer information.");
    }

    return *producer;
}



const BuildingInformation::Sanity& BuildingInformation::getSanityConf() const
{
    if (sanity == nullptr) {
        throw UnexpectedException("This building conf does not have sanity information.");
    }

    return *sanity;
}



const BuildingInformation::School& BuildingInformation::getSchoolConf() const
{
    if (school == nullptr) {
        throw UnexpectedException("This building conf does not have school information.");
    }

    return *school;
}



const BuildingInformation::Storage& BuildingInformation::getStorageConf() const
{
    if (storage == nullptr) {
        throw UnexpectedException("This building conf does not have storage information.");
    }

    return *storage;
}



void BuildingInformation::loadSpecificConf(const ModelReader& model)
{
    switch (type) {
        case Type::Farm:
            farm = new Farm(model);
            break;

        case Type::House:
            house = new House(model);
            break;

        case Type::Laboratory:
            laboratory = new Laboratory(model);
            break;

        case Type::Producer:
            producer = new Producer(model);
            break;

        case Type::Sanity:
            sanity = new Sanity(model);
            break;

        case Type::School:
            school = new School(model);
            break;

        case Type::Storage:
            storage = new Storage(model);
            break;

        default:
            break;
    }
}



BuildingInformation::Type BuildingInformation::resolveType(const QString& type)
{
    if (type == "farm")          return Type::Farm;
    if (type == "house")         return Type::House;
    if (type == "laboratory")    return Type::Laboratory;
    if (type == "mapEntryPoint") return Type::MapEntryPoint;
    if (type == "producer")      return Type::Producer;
    if (type == "road")          return Type::Road;
    if (type == "sanity")        return Type::Sanity;
    if (type == "school")        return Type::School;
    if (type == "storage")       return Type::Storage;

    throw BadConfigurationException("Unknown building of type \"" + type + "\".");
}



BuildingInformation::Common::Common(const ModelReader& model) :
    title(model.getString("title")),
    size(model.getOptionalInt("size", 1)),
    price(model.getOptionalInt("price", 0)),
    maxWorkers(model.getOptionalInt("workers", 0)),
    fireRiskIncrement(model.getOptionalInt("fireRisk", 0)),
    damageRiskIncrement(model.getOptionalInt("damageRisk", 0)),
    areaDescription()
{

}



BuildingInformation::Common::~Common()
{
    qDeleteAll(areaDescription);
}



BuildingInformation::Graphics::~Graphics()
{
    qDeleteAll(activeAnimation);
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



BuildingInformation::Farm::Farm(const ModelReader& model) :
    producedItemConf(model.getItemConf("producedItem")),
    harvestMonth(model.getInt("harvestMonth")),
    maxQuantityHarvested(model.getOptionalInt("maxQuantityHarvested", 8)),
    deliveryManConf(model.getOptionalCharacterConf("deliveryMan", "deliveryMan"))
{

}



BuildingInformation::House::House(const ModelReader& model) :
    populationPerImmigrant(model.getInt("populationPerImmigrant")),
    populationCapacity(model.getInt("populationCapacity"))
{

}



BuildingInformation::Laboratory::Laboratory(const ModelReader& model) :
    acceptedStudent(model.getCharacterConf("acceptedStudent")),
    producingInterval(model.getOptionalInt("producingCredits", 64) * BUILDING_CYCLES_PER_SECOND),
    emittedScientist(
        model.getOptionalCharacterConf("emittedScientist", acceptedStudent),
        model.getOptionalInt("scientistGenerationInterval", 4) * BUILDING_CYCLES_PER_SECOND,
        1
    )
{

}



BuildingInformation::Producer::Producer(const ModelReader& model) :
    producedItemConf(model.getItemConf("producedItem")),
    rawMaterialConf(model.getNatureElementConf("rawMaterialItem")),
    miner(
        model.getCharacterConf("minerCharacter"),
        model.getOptionalInt("minerGenerationInterval", 4) * BUILDING_CYCLES_PER_SECOND,
        model.getOptionalInt("maxSimultaneousMiners", 2)
    ),
    miningQuantity(model.getOptionalInt("miningQuantity", 25)),
    rawMaterialQuantityToProduce(model.getOptionalInt("rawMaterialQuantityToProduce", 100)),
    maxStoredRawMaterialQuantity(model.getOptionalInt("maxStoredRawMaterialQuantity", 500)),
    deliveryManConf(model.getOptionalCharacterConf("deliveryMan", "deliveryMan"))
{

}



BuildingInformation::Sanity::Sanity(const ModelReader& model) :
    walker(
        model.getCharacterConf("walkerCharacter"),
        model.getOptionalInt("walkerGenerationInterval", 8) * BUILDING_CYCLES_PER_SECOND,
        1
    )
{

}



BuildingInformation::School::School(const ModelReader& model) :
    student(
        model.getCharacterConf("studentCharacter"),
        model.getOptionalInt("studentGenerationInterval", 8) * BUILDING_CYCLES_PER_SECOND
    ),
    targetLaboratory(model.getBuildingConf("targetLaboratory"))
{

}




BuildingInformation::Storage::Storage(const ModelReader& model) :
    allowedItems(model.getListOfItemConfs("items")),
    maxQuantity(model.getOptionalInt("maxQuantity", 32)),
    autoRedistribute(model.getOptionalBool("autoRedistribute", true))
{

}



bool BuildingInformation::Storage::isItemAllowed(const ItemInformation& conf) const
{
    return allowedItems.contains(&conf);
}
