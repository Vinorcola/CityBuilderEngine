#include "Conf.hpp"

#include <yaml-cpp/yaml.h>



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
        auto elementInformation(new DynamicElementInformation(this, key, node.second));
        dynamicElements.insert(key, elementInformation);
    }

    // Load static element configuration.
    for (auto node : configurationRoot["staticElements"]) {
        QString key(QString::fromStdString(node.first.as<std::string>()));
        StaticElementInformation::checkModel(key, node.second);
        auto elementInformation(new StaticElementInformation(this, this, key, node.second));
        staticElements.insert(key, elementInformation);
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
