#ifndef MAPLOADER_HPP
#define MAPLOADER_HPP

#include <QtCore/QSize>
#include <QtCore/QString>
#include <yaml-cpp/node/node.h>

#include "src/engine/map/MapCoordinates.hpp"
#include "src/engine/processing/CycleDate.hpp"

class MapLoader
{
    private:
        YAML::Node rootNode;

    public:
        explicit MapLoader(const QString& filePath);

        QSize getSize() const;

        CycleDate getDate() const;

        int getBudget() const;

        MapCoordinates getEntryPoint() const;

        YAML::Node getBuildings() const;

        YAML::Node getCharacters() const;

        YAML::Node getNatureElements() const;
};

#endif // MAPLOADER_HPP
