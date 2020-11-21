#ifndef MAPSCENE_HPP
#define MAPSCENE_HPP

#include <QtCore/QBasicTimer>
#include <QtCore/QHash>
#include <QtWidgets/QGraphicsScene>

#include "src/engine/map/MapArea.hpp"
#include "src/viewer/element/TileLocatorInterface.hpp"
#include "src/viewer/image/ImageLibrary.hpp"
#include "src/viewer/Positioning.hpp"
#include "src/defines.hpp"

class AbstractBuilding;
class AreaCheckerInterface;
class BuildingInformation;
class BuildingView;
class Character;
class CharacterView;
class Conf;
class ConstructionCursor;
class DynamicElement;
class Map;
class MapCoordinates;
class MapSize;
class NatureElement;
class RoadPathGeneratorInterface;
class SelectionElement;
class Tile;
struct BuildingState;
struct CharacterState;
struct MapState;
struct NatureElementState;
struct State;

/**
 * @brief The scene used to display all the tiles (and their content).
 */
class MapScene : public QGraphicsScene, public TileLocatorInterface
{
        Q_OBJECT

    private:
        const AreaCheckerInterface& areaChecker;
        const RoadPathGeneratorInterface& roadPathGenerator;
        ImageLibrary imageLibrary;
        Positioning positioning;
        QHash<QString, Tile*> tiles;
        QHash<qintptr, BuildingView*> buildings;
        QHash<qintptr, CharacterView*> characters;
        optional<owner<ConstructionCursor*>> selectionElement;
        QBasicTimer animationClock;
        MapCoordinates currentTileLocation;

    public:
        MapScene(
            const Conf& conf,
            const AreaCheckerInterface& areaChecker,
            const RoadPathGeneratorInterface& roadPathGenerator,
            const MapState& mapState,
            const State& initialState
        );
        ~MapScene();

        virtual Tile& getTileAt(const MapCoordinates& location) const override;

    public slots:
        /**
         * @brief Request the tool for positioning a building.
         */
        void requestBuildingPositioning(const BuildingInformation& elementConf);

        void registerNewBuilding(const BuildingState& buildingState);
        void registerNewCharacter(const CharacterState& characterState);
        void registerNewNatureElement(const NatureElementState& natureElementState);

        /**
         * @brief Refresh the map.
         */
        void refresh(const State& state);

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
