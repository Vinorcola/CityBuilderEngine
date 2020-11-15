#ifndef CITYLOADER_HPP
#define CITYLOADER_HPP

#include <QtCore/QList>
#include <yaml-cpp/node/node.h>

#include "src/engine/map/MapCoordinates.hpp"

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
            QString type;
            MapCoordinates location;

            Building(YAML::Node node);
        };
        struct NatureElement {
            QString type;
            MapCoordinates location;

            NatureElement(YAML::Node node);
        };

    private:
        YAML::Node rootNode;

    public:
        explicit CityLoader(const QString& filePath);

        QString getTitle() const;
        CycleDate getStartDate() const;
        int getInitialBudget() const;

        QSize getMapSize() const;
        MapCoordinates getMapEntryPoint() const;
        QList<const Building> getInitialBuildings() const;
        QList<const NatureElement> getInitialNatureElements() const;
};

#endif // CITYLOADER_HPP
