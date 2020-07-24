#include "Conf.hpp"

#include <yaml-cpp/yaml.h>

#include "global/conf/BuildingInformation.hpp"
#include "global/conf/CharacterInformation.hpp"
#include "global/conf/ControlPanelElementInformation.hpp"



Conf::Conf(QObject* parent, const QString& filePath) :
    QObject(parent),
    buildings(),
    characters(),
    controlPanelElements()
{
    // Load file.
    YAML::Node configurationRoot(YAML::LoadFile(filePath.toStdString()));

    // Load characters' configuration.
    for (auto node : configurationRoot["characters"]) {
        QString key(QString::fromStdString(node.first.as<std::string>()));
        characters.insert(key, new CharacterInformation(this, key, node.second));
    }

    // Load buildings' configuration.
    for (auto node : configurationRoot["buildings"]) {
        QString key(QString::fromStdString(node.first.as<std::string>()));
        BuildingInformation::checkModel(key, node.second);
        buildings.insert(key, new BuildingInformation(this, this, key, node.second));
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



const CharacterInformation* Conf::getCharacterConf(const QString& elementKey) const
{
    return characters.value(elementKey);
}



const BuildingInformation* Conf::getBuildingConf(const QString& elementKey) const
{
    return buildings.value(elementKey);
}



const QList<ControlPanelElementInformation*> Conf::getControlPanelElements() const
{
    return controlPanelElements;
}
