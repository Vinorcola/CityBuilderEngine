#include "CityLoader.hpp"

#include <QtCore/QSize>
#include <yaml-cpp/yaml.h>

#include "src/engine/processing/CycleDate.hpp"
#include "src/global/yamlLibraryEnhancement.hpp"



CityLoader::Building::Building(YAML::Node node) :
    type(node["type"].as<QString>()),
    location(node["position"]["x"].as<int>(), node["position"]["y"].as<int>())
{

}



CityLoader::NatureElement::NatureElement(YAML::Node node) :
    type(node["type"].as<QString>()),
    location(node["position"]["x"].as<int>(), node["position"]["y"].as<int>())
{

}



CityLoader::CityLoader(const QString& filePath) :
    rootNode(YAML::LoadFile(filePath.toStdString()))
{

}



QString CityLoader::getTitle() const
{
    return rootNode["title"].as<QString>();
}



CycleDate CityLoader::getStartDate() const
{
    return CycleDate(
        rootNode["date"]["year"].as<int>(),
        rootNode["date"]["month"].as<int>(),
        rootNode["date"]["cycles"].as<int>()
    );
}



int CityLoader::getInitialBudget() const
{
    return rootNode["budget"].as<int>();
}



QSize CityLoader::getMapSize() const
{
    return rootNode["map"]["size"].as<QSize>();
}



TileCoordinates CityLoader::getMapEntryPoint() const
{
    return {
        rootNode["map"]["entryPoint"]["x"].as<int>(),
        rootNode["map"]["entryPoint"]["y"].as<int>(),
    };
}



QList<CityLoader::Building> CityLoader::getInitialBuildings() const
{
    QList<Building> buildings;
    for (auto node : rootNode["map"]["buildings"]) {
        buildings.append(node);
    }

    return buildings;
}



QList<CityLoader::NatureElement> CityLoader::getInitialNatureElements() const
{
    QList<NatureElement> natureElements;
    for (auto node : rootNode["map"]["natureElements"]) {
        natureElements.append(node);
    }

    return natureElements;
}
