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
        dynamicElements[elementInformation->getType()] = elementInformation;
    }

    // Load static element configuration.
    for (auto node : configurationRoot["staticElements"]) {
        QString key(QString::fromStdString(node.first.as<std::string>()));
        auto elementInformation(new StaticElementInformation(this, key, node.second));
        staticElements[elementInformation->getType()] = elementInformation;
    }
}



const DynamicElementInformation*Conf::getDynamicElementConf(DynamicElementInformation::Type type) const
{
    return dynamicElements.value(type);
}



const StaticElementInformation*Conf::getStaticElementConf(StaticElementInformation::Type type) const
{
    return staticElements.value(type);
}
