#ifndef CITYLOADER_HPP
#define CITYLOADER_HPP

#include <QtCore/QList>
#include <yaml-cpp/node/node.h>

#include "src/global/geometry/TileCoordinates.hpp"

class CycleDate;
class QString;
class QSize;

/**
 * @brief Loads a city file.
 *
 * City file contains information about a city and it's initial state.
 */
class CityLoader
{
    public:
        struct Building {
            Building(YAML::Node node);
            QString type;
            TileCoordinates location;
        };
        struct NatureElement {
            NatureElement(YAML::Node node);
            QString type;
            TileCoordinates location;
        };

    private:
        YAML::Node rootNode;

    public:
        explicit CityLoader(const QString& filePath);

        QString getTitle() const;
        CycleDate getStartDate() const;
        int getInitialBudget() const;

        QSize getMapSize() const;
        TileCoordinates getMapEntryPoint() const;
        QList<Building> getInitialBuildings() const;
        QList<NatureElement> getInitialNatureElements() const;
};

#endif // CITYLOADER_HPP
