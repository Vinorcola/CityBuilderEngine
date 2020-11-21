#ifndef BUILDINGVIEW_HPP
#define BUILDINGVIEW_HPP

#include "src/defines.hpp"

class AbstractBuilding;
class BuildingImage;
class ImageLibrary;
class MapSize;
class Positioning;
class StaticElement;
class Tile;
class TileLocatorInterface;
struct BuildingState;

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
        int currentStateVersion;
        int animationIndex;

    public:
        BuildingView(
            const Positioning& positioning,
            const TileLocatorInterface& tileLocator,
            const ImageLibrary& imageLibrary,
            const BuildingState& state
        );
        ~BuildingView();

        void update(const BuildingState& state);
        void destroy();

        void advanceAnimation();

    private:
        void maskCoveredTiles();
        void revealCoveredTiles();
};

#endif // BUILDINGVIEW_HPP
