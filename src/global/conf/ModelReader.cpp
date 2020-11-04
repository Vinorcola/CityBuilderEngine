#include "ModelReader.hpp"

#include "src/exceptions/BadConfigurationException.hpp"
#include "src/global/conf/Conf.hpp"
#include "src/global/yamlLibraryEnhancement.hpp"



ModelReader::ModelReader(const Conf& conf, const QString& key, const YAML::Node& node) :
    conf(conf),
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



const ModelReader ModelReader::getSubModel(const char key[]) const
{
    if (!node[key] || !node[key].IsMap()) {
        throw BadConfigurationException(generateErrorMessage(key, "an object"));
    }

    return { conf, key, node[key] };
}



int ModelReader::getInt(const char key[]) const
{
    if (!node[key]) {
        throw BadConfigurationException(generateErrorMessage(key, "a number"));
    }

    return node[key].as<int>();
}



qreal ModelReader::getReal(const char key[]) const
{
    if (!node[key]) {
        throw BadConfigurationException(generateErrorMessage(key, "a number"));
    }

    return node[key].as<qreal>();
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
        throw BadConfigurationException(generateErrorMessage(key, "some map coordinates"));
    }

    return node[key].as<MapCoordinates>();
}



QPoint ModelReader::getPoint(const char key[]) const
{
    if (!node[key]) {
        throw BadConfigurationException(generateErrorMessage(key, "some point coordinates"));
    }

    return node[key].as<QPoint>();
}



QList<QPoint> ModelReader::getPointList(const char key[]) const
{
    if (!node[key] || !node[key].IsSequence()) {
        throw BadConfigurationException(generateErrorMessage(key, "a list of point coordinates"));
    }

    QList<QPoint> list;
    for (auto subNode: node[key]) {
        list.append(subNode.as<QPoint>());
    }

    return list;
}



const BuildingInformation& ModelReader::getBuildingConf(const char key[]) const
{
    return conf.getBuildingConf(getString(key));
}



const CharacterInformation& ModelReader::getCharacterConf(const char key[]) const
{
    return conf.getCharacterConf(getString(key));
}



const ItemInformation& ModelReader::getItemConf(const char key[]) const
{
    return conf.getItemConf(getString(key));
}



QList<const ItemInformation*> ModelReader::getListOfItemConfs(const char key[]) const
{
    if (!node[key]) {
        throw BadConfigurationException(generateErrorMessage(key, "a list of items"));
    }

    QList<const ItemInformation*> list;
    for (auto subNode: node[key]) {
        list.append(&conf.getItemConf(subNode.as<QString>()));
    }

    return list;
}



const NatureElementInformation& ModelReader::getNatureElementConf(const char key[]) const
{
    return conf.getNatureElementConf(getString(key));
}



bool ModelReader::getOptionalBool(const char key[], const bool defaultValue) const
{
    if (!node[key]) {
        return defaultValue;
    }

    return node[key].as<bool>();
}



int ModelReader::getOptionalInt(const char key[], const int defaultValue) const
{
    if (!node[key]) {
        return defaultValue;
    }

    return node[key].as<int>();
}



QString ModelReader::getOptionalString(const char key[], const QString& defaultValue) const
{
    if (!node[key]) {
        return defaultValue;
    }

    return node[key].as<QString>();
}



QPoint ModelReader::getOptionalPoint(const char key[], const QPoint& defaultValue) const
{
    if (!node[key]) {
        return defaultValue;
    }

    return node[key].as<QPoint>();
}



QList<QPoint> ModelReader::getOptionalPointList(const char key[]) const
{
    QList<QPoint> list;
    if (!node[key] || !node[key].IsSequence()) {
        return list;
    }

    for (auto subNode: node[key]) {
        list.append(subNode.as<QPoint>());
    }

    return list;
}



const CharacterInformation& ModelReader::getOptionalCharacterConf(const char key[], const CharacterInformation& defaultValue) const
{
    if (!node[key]) {
        return defaultValue;
    }

    return conf.getCharacterConf(getString(key));
}



const CharacterInformation& ModelReader::getOptionalCharacterConf(const char key[], const QString defaultValue) const
{
    return conf.getCharacterConf(getOptionalString(key, defaultValue));
}



const QString ModelReader::generateErrorMessage(const char key[], const char expected[]) const
{
    return QString("Could not found required key \"") + key + "\" in \"" + this->key + "\". Expected " + expected + ".";
}
