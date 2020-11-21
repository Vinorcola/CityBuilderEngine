#include "CityLoader.hpp"

#include <QtCore/QSize>
#include <yaml-cpp/yaml.h>

#include "src/engine/processing/CycleDate.hpp"
#include "src/global/yamlLibraryEnhancement.hpp"



CityLoader::Building::Building(YAML::Node node) :
    type(node["type"].as<QString>()),
    location(node["position"].as<MapCoordinates>())
{

}



CityLoader::NatureElement::NatureElement(YAML::Node node) :
    type(node["type"].as<QString>()),
    location(node["position"].as<MapCoordinates>())
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



MapCoordinates CityLoader::getMapEntryPoint() const
{
    return rootNode["map"]["entryPoint"].as<MapCoordinates>();
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
