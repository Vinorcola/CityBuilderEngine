#ifndef BUILDINGVIEW_HPP
#define BUILDINGVIEW_HPP

#include "src/engine/state/BuildingState.hpp"
#include "src/defines.hpp"

class AbstractBuilding;
class BuildingImage;
class ImageLibrary;
class MapSize;
class Positioning;
class StaticElement;
class Tile;
class TileLocatorInterface;

/**
 * @brief Handles the graphical representation of a building.
 *
 * It knows all the logic needed to update the graphics according to the given state of the building.
 */
class BuildingView
{
    private:
        const TileLocatorInterface& tileLocator;
        const MapSize& buildingSize;
        Tile& tile;
        const BuildingImage& image;
        owner<StaticElement*> graphicElement;
        BuildingState currentState;
        int animationIndex;

    public:
        BuildingView(
            const Positioning& positioning,
            const TileLocatorInterface& tileLocator,
            const ImageLibrary& imageLibrary,
            const BuildingState& state
        );
        ~BuildingView();

        const BuildingState& getCurrentState() const;

        void update(const BuildingState& state);
        void destroy();

        void advanceAnimation();

    private:
        void maskCoveredTiles();
        void revealCoveredTiles();
        void updateStatus(BuildingState::Status newStatus);
};

#endif // BUILDINGVIEW_HPP
