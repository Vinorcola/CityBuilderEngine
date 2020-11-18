#include "Conf.hpp"

#include <yaml-cpp/yaml.h>

#include "src/exceptions/BadConfigurationException.hpp"
#include "src/exceptions/OutOfRangeException.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/CharacterInformation.hpp"
#include "src/global/conf/ControlPanelElementInformation.hpp"
#include "src/global/conf/ItemInformation.hpp"
#include "src/global/conf/ModelReader.hpp"
#include "src/global/conf/NatureElementInformation.hpp"
#include "src/global/yamlLibraryEnhancement.hpp"



Conf::Conf(const QString& filePath) :
    tileSize(),
    items(),
    buildings(),
    characters(),
    natureElements(),
    controlPanelElements()
{
    // Load file.
    YAML::Node configurationRoot(YAML::LoadFile(filePath.toStdString()));

    // Load graphics' configuration.
    if (!configurationRoot["graphics"] || !configurationRoot["graphics"]["tileHeight"]) {
        throw BadConfigurationException("Expected the tile height to be configured in \"graphics.tileHeight\".");
    }
    tileSize.setHeight(configurationRoot["graphics"]["tileHeight"].as<int>());
    tileSize.setWidth((tileSize.height() - 1) * 2);

    // Load nature elements' configuration.
    for (auto node : configurationRoot["natureElements"]) {
        QString key(node.first.as<QString>());
        NatureElementInformation::checkModel(key, node.second);
        natureElements.insert(key, new NatureElementInformation(key, node.second));
    }

    // Load item's configuration.
    for (auto node : configurationRoot["items"]) {
        QString key(node.first.as<QString>());
        ItemInformation::checkModel(key, node.second);
        items.insert(key, new ItemInformation(key, node.second));
    }

    // Load characters' configuration.
    for (auto node : configurationRoot["characters"]) {
        QString key(node.first.as<QString>());
        characters.insert(key, new CharacterInformation(ModelReader(*this, key, node.second)));
    }

    // Load buildings' configuration.
    for (auto node : configurationRoot["buildings"]) {
        QString key(node.first.as<QString>());
        buildings.insert(key, new BuildingInformation(ModelReader(*this, key, node.second)));
    }
    // We load building's specific configuration later because we may have dependencies between buildings: we need all
    // the buildings to be defined before loading specifics configuration.
    for (auto node : configurationRoot["buildings"]) {
        QString key(node.first.as<QString>());
        buildings[key]->loadSpecificConf(ModelReader(*this, key, node.second));
    }

    // Load control panel items.
    for (auto node : configurationRoot["controlPanel"]["content"]) {
        ControlPanelElementInformation::checkModel(node);
        controlPanelElements.append(new ControlPanelElementInformation(*this, node));
    }
}



Conf::~Conf()
{
    qDeleteAll(items);
    qDeleteAll(buildings);
    qDeleteAll(characters);
    qDeleteAll(natureElements);
    qDeleteAll(controlPanelElements);
}



const QSize& Conf::getTileSize() const
{
    return tileSize;
}



const ItemInformation& Conf::getItemConf(const QString& key) const
{
    if (!items.contains(key)) {
        throw OutOfRangeException("Item of type \"" + key + "\" does not exists.");
    }

    return *items.value(key);
}



QList<QString> Conf::getAllBuildingKeys() const
{
    return buildings.keys();
}



const BuildingInformation& Conf::getBuildingConf(const QString& key) const
{
    if (!buildings.contains(key)) {
        throw OutOfRangeException("Building of type \"" + key + "\" does not exists.");
    }

    return *buildings.value(key);
}



QList<QString> Conf::getAllCharacterKeys() const
{
    return characters.keys();
}



const CharacterInformation& Conf::getCharacterConf(const QString& key) const
{
    if (!characters.contains(key)) {
        throw OutOfRangeException("Character of type \"" + key + "\" does not exists.");
    }

    return *characters.value(key);
}



QList<QString> Conf::getAllNatureElementKeys() const
{
    return natureElements.keys();
}



const NatureElementInformation& Conf::getNatureElementConf(const QString& key) const
{
    if (!natureElements.contains(key)) {
        throw OutOfRangeException("Nature element of type \"" + key + "\" does not exists.");
    }

    return *natureElements.value(key);
}



const QList<ControlPanelElementInformation*> Conf::getControlPanelElements() const
{
    return controlPanelElements;
}
