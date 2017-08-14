#ifndef YAMLLIBRARYENHANCEMENT_HPP
#define YAMLLIBRARYENHANCEMENT_HPP

#include <QtCore/QString>
#include <yaml-cpp/node/convert.h>

namespace YAML {

template<>
struct convert<QString>
{
    static Node encode(const QString& rhs)
    {
        return Node(rhs.toStdString());
    }

    static bool decode(const Node& node, QString& rhs)
    {
        if (!node.IsScalar())
            return false;
        rhs = QString::fromStdString(node.Scalar());
        return true;
    }
};

}

#endif // YAMLLIBRARYENHANCEMENT_HPP
