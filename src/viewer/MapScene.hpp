#ifndef MAPSCENE_HPP
#define MAPSCENE_HPP

#include <QtCore/QBasicTimer>
#include <QtWidgets/QGraphicsScene>

#include "src/engine/map/MapArea.hpp"
#include "src/viewer/element/TileLocatorInterface.hpp"
#include "src/viewer/Positioning.hpp"
#include "src/defines.hpp"

class Building;
class BuildingInformation;
class BuildingView;
class Character;
class CharacterView;
class Conf;
class ConstructionCursor;
class DynamicElement;
class ImageLibrary;
class Map;
class MapCoordinates;
class MapSize;
class NatureElement;
class SelectionElement;
class Tile;

/**
 * @brief The scene used to display all the tiles (and their content).
 */
class MapScene : public QGraphicsScene, public TileLocatorInterface
{
        Q_OBJECT

    private:
        const Map& map;
        const ImageLibrary& imageLibrary;
        Positioning positioning;
        QList<owner<Tile*>> tiles;
        QList<owner<BuildingView*>> buildings;
        QList<owner<CharacterView*>> characters;
        optional<owner<ConstructionCursor*>> selectionElement;
        QBasicTimer animationClock;
        MapCoordinates currentTileLocation;

    public:
        MapScene(const Conf& conf, const Map& map, const ImageLibrary& imageLibrary);

        ~MapScene();

        /**
         * @brief Request the tool for positioning a building.
         */
        void requestBuildingPositioning(const BuildingInformation& elementConf);

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
        virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    signals:
        /**
         * @brief Indicate the user requested a building creation.
         *
         * @param buildingKey The type of building.
         * @param area        The area of construction.
         */
        void buildingCreationRequested(const BuildingInformation& elementConf, MapArea area);
};

#endif // MAPSCENE_HPP
