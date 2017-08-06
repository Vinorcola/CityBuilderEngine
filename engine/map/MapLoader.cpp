#include "MapLoader.hpp"

#include <yaml-cpp/yaml.h>



MapLoader::MapLoader(const QString& filePath) :
    rootNode(YAML::LoadFile(filePath.toStdString()))
{

}



QSize MapLoader::getSize() const
{
    return { rootNode["size"]["width"].as<int>(), rootNode["size"]["height"].as<int>() };
}



int MapLoader::getBudget() const
{
    return rootNode["status"]["budget"].as<int>();
}



YAML::Node MapLoader::getStaticElements() const
{
    return rootNode["staticElements"];
}
