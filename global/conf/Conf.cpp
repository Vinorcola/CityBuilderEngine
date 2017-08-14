#include "Conf.hpp"

#include <yaml-cpp/yaml.h>

#include "global/conf/ControlPanelElementInformation.hpp"
#include "global/conf/DynamicElementInformation.hpp"
#include "global/conf/StaticElementInformation.hpp"



Conf::Conf(QObject* parent, const QString& filePath) :
    QObject(parent),
    dynamicElements(),
    staticElements()
{
    // Load file.
    YAML::Node configurationRoot(YAML::LoadFile(filePath.toStdString()));

    // Load dynamic element configuration.
    for (auto node : configurationRoot["dynamicElements"]) {
        QString key(QString::fromStdString(node.first.as<std::string>()));
        dynamicElements.insert(key, new DynamicElementInformation(this, key, node.second));
    }

    // Load static element configuration.
    for (auto node : configurationRoot["staticElements"]) {
        QString key(QString::fromStdString(node.first.as<std::string>()));
        StaticElementInformation::checkModel(key, node.second);
        staticElements.insert(key, new StaticElementInformation(this, this, key, node.second));
    }

    // Resolve dependencies.
    for (auto element : staticElements) {
        element->resolveDependencies(this);
    }

    // Load control panel items.
    for (auto node : configurationRoot["controlPanel"]["content"]) {
        ControlPanelElementInformation::checkModel(node);
        controlPanelElements.append(new ControlPanelElementInformation(this, this, node));
    }
}



const DynamicElementInformation* Conf::getDynamicElementConf(const QString& elementKey) const
{
    return dynamicElements.value(elementKey);
}



const StaticElementInformation* Conf::getStaticElementConf(const QString& elementKey) const
{
    return staticElements.value(elementKey);
}



const QList<ControlPanelElementInformation*> Conf::getControlPanelElements() const
{
    return controlPanelElements;
}
