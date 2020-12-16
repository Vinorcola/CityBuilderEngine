#ifndef YAMLLIBRARYENHANCEMENT_HPP
#define YAMLLIBRARYENHANCEMENT_HPP

#include <QtCore/QPoint>
#include <QtCore/QSize>
#include <QtCore/QString>
#include <yaml-cpp/node/convert.h>

#include "src/global/geometry/TileCoordinates.hpp"

namespace YAML {

template<>
struct convert<QString>
{
    static Node encode(const QString& string)
    {
        return Node(string.toStdString());
    }

    static bool decode(const Node& node, QString& string)
    {
        if (!node.IsScalar()) {
            return false;
        }
        string = QString::fromStdString(node.Scalar());

        return true;
    }
};

template<>
struct convert<QPoint>
{
    static bool decode(const Node& node, QPoint& position)
    {
        if (!node.IsMap() || !node["x"] || !node["y"]) {
            return false;
        }
        position.setX(node["x"].as<int>());
        position.setY(node["y"].as<int>());

        return true;
    }
};

template<>
struct convert<QSize>
{
    static bool decode(const Node& node, QSize& size)
    {
        if (!node.IsMap() || !node["width"] || !node["height"]) {
            return false;
        }
        size.setWidth(node["width"].as<int>());
        size.setHeight(node["height"].as<int>());

        return true;
    }
};

}

#endif // YAMLLIBRARYENHANCEMENT_HPP
