#include "Conf.hpp"

#include <yaml-cpp/yaml.h>

#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/CharacterInformation.hpp"
#include "src/global/conf/ControlPanelElementInformation.hpp"
#include "src/global/conf/ItemInformation.hpp"
#include "src/global/conf/NatureElementInformation.hpp"
#include "src/global/yamlLibraryEnhancement.hpp"



Conf::Conf(QObject* parent, const QString& filePath) :
    QObject(parent),
    items(),
    buildings(),
    characters(),
    natureElements(),
    controlPanelElements()
{
    // Load file.
    YAML::Node configurationRoot(YAML::LoadFile(filePath.toStdString()));

    // Load item's configuration.
    for (auto node : configurationRoot["items"]) {
        QString key(node.first.as<QString>());
        ItemInformation::checkModel(key, node.second);
        items.insert(key, new ItemInformation(this, key, node.second));
    }

    // Load characters' configuration.
    for (auto node : configurationRoot["characters"]) {
        QString key(node.first.as<QString>());
        characters.insert(key, new CharacterInformation(this, key, node.second));
    }

    // Load buildings' configuration.
    for (auto node : configurationRoot["buildings"]) {
        QString key(node.first.as<QString>());
        BuildingInformation::checkModel(key, node.second);
        buildings.insert(key, new BuildingInformation(this, this, key, node.second));
    }

    // Load nature elements' configuration.
    for (auto node : configurationRoot["natureElements"]) {
        QString key(node.first.as<QString>());
        NatureElementInformation::checkModel(key, node.second);
        natureElements.insert(key, new NatureElementInformation(this, key, node.second));
    }

    // Resolve dependencies.
    for (auto element : buildings) {
        element->resolveDependencies(this);
    }

    // Load control panel items.
    for (auto node : configurationRoot["controlPanel"]["content"]) {
        ControlPanelElementInformation::checkModel(node);
        controlPanelElements.append(new ControlPanelElementInformation(this, this, node));
    }
}



const ItemInformation* Conf::getItemConf(const QString& key) const
{
    return items.value(key);
}



const BuildingInformation* Conf::getBuildingConf(const QString& key) const
{
    return buildings.value(key);
}



const CharacterInformation* Conf::getCharacterConf(const QString& key) const
{
    return characters.value(key);
}



const NatureElementInformation* Conf::getNatureElementConf(const QString& key) const
{
    return natureElements.value(key);
}



const QList<ControlPanelElementInformation*> Conf::getControlPanelElements() const
{
    return controlPanelElements;
}
