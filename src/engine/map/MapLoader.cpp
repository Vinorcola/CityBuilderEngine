#include "MapLoader.hpp"

#include <yaml-cpp/yaml.h>

#include "src/engine/processing/CycleDate.hpp"



MapLoader::MapLoader(const QString& filePath) :
    rootNode(YAML::LoadFile(filePath.toStdString()))
{

}



QSize MapLoader::getSize() const
{
    return { rootNode["size"]["width"].as<int>(), rootNode["size"]["height"].as<int>() };
}



CycleDate MapLoader::getDate() const
{
    return CycleDate(
        rootNode["status"]["date"]["year"].as<int>(),
        rootNode["status"]["date"]["month"].as<int>(),
        rootNode["status"]["date"]["cycles"].as<int>()
    );
}



int MapLoader::getBudget() const
{
    return rootNode["status"]["budget"].as<int>();
}



YAML::Node MapLoader::getBuildings() const
{
    return rootNode["buildings"];
}



YAML::Node MapLoader::getCharacters() const
{
    return rootNode["characters"];
}



YAML::Node MapLoader::getNatureElements() const
{
    return rootNode["natureElements"];
}
