#ifndef MODELREADER_HPP
#define MODELREADER_HPP

#include <QtCore/QString>

#include "src/engine/map/MapCoordinates.hpp"

namespace YAML {
    class Node;
}

class ModelReader
{
    private:
        const QString& key;
        const YAML::Node& node;

    public:
        ModelReader(const QString& key, const YAML::Node& node);

        const QString& getKey() const;

        const YAML::Node& getNode() const;

        int getInt(const char key[]) const;

        QString getString(const char key[]) const;

        MapCoordinates getMapCoordinates(const char key[]) const;

        int getOptionalInt(const char key[], const int defaultValue = 0) const;

    private:
        const QString generateErrorMessage(const char key[], const char expected[]) const;
};

#endif // MODELREADER_HPP
