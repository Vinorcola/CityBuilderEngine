#ifndef MAPLOADER_HPP
#define MAPLOADER_HPP

#include <QtCore/QSize>
#include <QtCore/QString>
#include <yaml-cpp/node/node.h>

class MapLoader
{
    private:
        YAML::Node rootNode;

    public:
        explicit MapLoader(const QString& filePath);

        QSize getSize() const;

        int getBudget() const;

        YAML::Node getStaticElements() const;
};

#endif // MAPLOADER_HPP
