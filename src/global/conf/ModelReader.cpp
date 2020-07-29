#include "ModelReader.hpp"

#include "src/exceptions/BadConfigurationException.hpp"
#include "src/global/yamlLibraryEnhancement.hpp"



ModelReader::ModelReader(const QString& key, const YAML::Node& node) :
    key(key),
    node(node)
{

}



const QString& ModelReader::getKey() const
{
    return key;
}



const YAML::Node& ModelReader::getNode() const
{
    return node;
}



int ModelReader::getInt(const char key[]) const
{
    if (!node[key]) {
        throw BadConfigurationException(generateErrorMessage(key, "a number"));
    }

    return node[key].as<int>();
}



QString ModelReader::getString(const char key[]) const
{
    if (!node[key]) {
        throw BadConfigurationException(generateErrorMessage(key, "a string"));
    }

    return node[key].as<QString>();
}



MapCoordinates ModelReader::getMapCoordinates(const char key[]) const
{
    if (!node[key]) {
        throw BadConfigurationException(generateErrorMessage(key, "some coordinates"));
    }

    return node[key].as<MapCoordinates>();
}



int ModelReader::getOptionalInt(const char key[], const int defaultValue) const
{
    if (!node[key]) {
        return defaultValue;
    }

    return node[key].as<int>();
}



const QString ModelReader::generateErrorMessage(const char key[], const char expected[]) const
{
    return QString("Could not found required key \"") + key + "\" in \"" + this->key + "\". Expected " + expected + ".";
}
