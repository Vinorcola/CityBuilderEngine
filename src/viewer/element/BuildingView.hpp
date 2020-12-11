#ifndef BUILDINGVIEW_HPP
#define BUILDINGVIEW_HPP

#include "src/engine/state/BuildingState.hpp"
#include "src/viewer/element/graphics/StaticElement.hpp"
#include "src/defines.hpp"

class AbstractBuilding;
class BuildingAreaPartImage;
class ImageLibrary;
class MapSize;
class Positioning;
class Tile;
class TileLocatorInterface;

/**
 * @brief Handles the graphical representation of a building.
 *
 * It knows all the logic needed to update the graphics according to the given state of the building. Note that a
 * building can have several area parts, which each a specific image to display. Each area part is squared, but the
 * whole building may be a rectangle.
 */
class BuildingView
{
    private:
        class AreaPart
        {
            private:
                const TileLocatorInterface& tileLocator;
                MapSize size;
                Tile& tile;
                const BuildingAreaPartImage& image;
                StaticElement graphicElement;
                int animationIndex;

            public:
                AreaPart(
                    const Positioning& positioning,
                    const TileLocatorInterface& tileLocator,
                    const MapCoordinates& leftCorner,
                    const MapSize& size,
                    const BuildingAreaPartImage& image
                );
                ~AreaPart();

                void advanceAnimation();
                void updateStatus(BuildingStatus status);

            private:
                void maskCoveredTiles();
                void revealCoveredTiles();
        };

    private:
        QList<owner<AreaPart*>> areaParts;
        BuildingState currentState;

    public:
        BuildingView(
            const Positioning& positioning,
            const TileLocatorInterface& tileLocator,
            const ImageLibrary& imageLibrary,
            const BuildingState& state
        );

        const BuildingState& getCurrentState() const;

        void update(const BuildingState& state);
        void destroy();

        void advanceAnimation();
};

#endif // BUILDINGVIEW_HPP
