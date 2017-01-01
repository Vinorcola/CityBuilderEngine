#include "Conf.hpp"

#include <yaml-cpp/yaml.h>





Conf::Conf(const QString& filePath) :
    staticElements()
{
    // Load file.
    YAML::Node configurationRoot(YAML::LoadFile(filePath.toStdString()));

    // Load static element configuration.
    for (auto node : configurationRoot["static_elements"])
    {
        QString key(QString::fromStdString(node.first.as<std::string>()));
        Owner<StaticElementInformation*> elementInformation(new StaticElementInformation(key, node.second["model"]));
        staticElements[elementInformation->getType()] = elementInformation;
    }
}
