#ifndef MAPSCENE_HPP
#define MAPSCENE_HPP

#include <QtCore/QBasicTimer>
#include <QtWidgets/QGraphicsScene>

#include "src/viewer/element/TileLocatorInterface.hpp"
#include "src/defines.hpp"

class Building;
class BuildingInformation;
class BuildingView;
class Character;
class CharacterView;
class Conf;
class DynamicElement;
class ImageLibrary;
class Map;
class MapArea;
class MapCoordinates;
class MapSize;
class NatureElement;
class SelectionElement;
class Tile;

class MapScene : public QGraphicsScene, public TileLocatorInterface
{
        Q_OBJECT

    private:
        const Map& map;
        const ImageLibrary& imageLibrary;
        QList<owner<Tile*>> tiles;
        QList<owner<BuildingView*>> buildings;
        QList<owner<CharacterView*>> characters;
        owner<SelectionElement*> selectionElement;
        QBasicTimer animationClock;

    public:
        MapScene(const Conf& conf, const Map& map, const ImageLibrary& imageLibrary);

        ~MapScene();

        /**
         * @brief Request the positioning of a building (trigger selection element).
         *
         * @param type The type of building the user wants to create.
         */
        void requestBuildingPositioning(const BuildingInformation* elementConf);

        /**
         * @brief Request a building creation.
         *
         * @param buildingKey The type of building.
         * @param area        The area of construction.
         */
        void requestBuildingCreation(const BuildingInformation* elementConf, const MapArea& area);

        virtual Tile& getTileAt(const MapCoordinates& location) const override;

    public slots:
        void registerNewBuilding(QSharedPointer<const Building> element);

        void registerNewCharacter(QSharedPointer<const Character> element);

        void registerNewNatureElement(const NatureElement& element);

        /**
         * @brief Refresh the map.
         */
        void refresh();

    protected:
        virtual void timerEvent(QTimerEvent* event) override;

    private:
        void maskCoveredTiles(Tile& tile, const MapSize& elementSize);

        /**
         * @brief Refresh the selection element.
         *
         * @note Please call only if element is visible.
         */
        void refreshSelectionElement();

    private slots:
        void currentTileChanged(Tile* currentTile);

    signals:
        /**
         * @brief Indicate the user requested a building creation.
         *
         * @param buildingKey The type of building.
         * @param area        The area of construction.
         */
        void buildingCreationRequested(const BuildingInformation& elementConf, const MapArea& area);
};

#endif // MAPSCENE_HPP
