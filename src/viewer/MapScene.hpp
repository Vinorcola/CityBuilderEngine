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

    public:
        MapScene(const Conf& conf, const Map& map, const ImageLibrary& imageLibrary);

        ~MapScene();

        /**
         * @brief Request the positioning of a building (trigger selection element).
         *
         * @param type The type of building the user wants to create.
         */
        void requestBuildingPositioning(const BuildingInformation* elementConf);

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

    private slots:
        void currentTileChanged(Tile* currentTile);

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
