#ifndef MAPSCENE_HPP
#define MAPSCENE_HPP

#include <QtCore/QBasicTimer>
#include <QtCore/QHash>
#include <QtWidgets/QGraphicsScene>

#include "src/global/geometry/TileCoordinates.hpp"
#include "src/global/Direction.hpp"
#include "src/viewer/element/TileLocatorInterface.hpp"
#include "src/viewer/image/ImageLibrary.hpp"
#include "src/viewer/Positioning.hpp"
#include "src/defines.hpp"

class AreaCheckerInterface;
class BuildingInformation;
class BuildingView;
class CharacterView;
class Conf;
class ConstructionCursor;
class DialogDisplayer;
class RoadPathGeneratorInterface;
class TileView;
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
        DialogDisplayer& dialogDisplayer;
        QHash<QString, owner<TileView*>> tiles;
        QHash<qintptr, owner<BuildingView*>> buildings;
        QHash<qintptr, owner<CharacterView*>> characters;
        QHash<QString, BuildingView*> buildingLocationCache; ///< A cache where key is a MapCoordinates has value.
        optional<owner<ConstructionCursor*>> selectionElement;
        QBasicTimer animationClock;
        TileCoordinates currentTileLocation;

    public:
        MapScene(
            const Conf& conf,
            const AreaCheckerInterface& areaChecker,
            const RoadPathGeneratorInterface& roadPathGenerator,
            DialogDisplayer& dialogDisplayer,
            const MapState& mapState,
            const State& initialState
        );
        ~MapScene();

        virtual TileView& getTileAt(const TileCoordinates& location) const override;

    public slots:
        /**
         * @brief Request the tool for positioning a building.
         */
        void requestBuildingPositioning(const BuildingInformation& elementConf);
        void requestBuildingRotation();

        void registerNewBuilding(const BuildingState& buildingState);
        void registerNewCharacter(const CharacterState& characterState);
        void registerNewNatureElement(const NatureElementState& natureElementState);

        /**
         * @brief Refresh the map.
         */
        void refresh(const State& state);

    protected:
        virtual void timerEvent(QTimerEvent* event) override;
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
        virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    signals:
        /**
         * @brief Indicate the user requested a building creation.
         *
         * @param elementConf The type of building.
         * @param leftCorner  The location of the left corner of the construction area.
         * @param orientation The orientation of the building.
         */
        void buildingCreationRequested(
            const BuildingInformation& elementConf,
            TileCoordinates leftCorner,
            Direction orientation
        );

    private:
        void displayBuildingDetailsDialog(const BuildingState& buildingState);
};

#endif // MAPSCENE_HPP
