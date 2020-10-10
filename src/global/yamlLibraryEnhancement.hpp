#ifndef YAMLLIBRARYENHANCEMENT_HPP
#define YAMLLIBRARYENHANCEMENT_HPP

#include <QtCore/QPoint>
#include <QtCore/QString>
#include <yaml-cpp/node/convert.h>

#include "src/engine/map/MapCoordinates.hpp"

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
struct convert<MapCoordinates>
{
    static bool decode(const Node& node, MapCoordinates& coordinates)
    {
        if (!node.IsMap() || !node["x"] || !node["y"]) {
            return false;
        }
        coordinates.setX(node["x"].as<qreal>());
        coordinates.setY(node["y"].as<qreal>());

        return true;
    }
};

template<>
struct convert<QPoint>
{
    static bool decode(const Node& node, QPoint& coordinates)
    {
        if (!node.IsMap() || !node["x"] || !node["y"]) {
            return false;
        }
        coordinates.setX(node["x"].as<int>());
        coordinates.setY(node["y"].as<int>());

        return true;
    }
};

}

#endif // YAMLLIBRARYENHANCEMENT_HPP
