#ifndef BUILDINGVIEW_HPP
#define BUILDINGVIEW_HPP

#include <QtCore/QSharedPointer>
#include <QtCore/QSizeF>
#include <QtCore/QWeakPointer>

#include "src/defines.hpp"

class Building;
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
 * It keeps a weak pointer to the engine data of the building and knows all the logic needed to update the graphics
 * according to those data.
 */
class BuildingView
{
    private:
        const TileLocatorInterface& tileLocator;
        QWeakPointer<const Building> engineData;
        const MapSize& buildingSize;
        Tile& tile;
        const BuildingImage& image;
        owner<StaticElement*> graphicElement;
        int currentViewVersion;
        int animationIndex;

    public:
        BuildingView(
            const Positioning& positioning,
            const TileLocatorInterface& tileLocator,
            const ImageLibrary& imageLibrary,
            const QSharedPointer<const Building>& engineData
        );

        ~BuildingView();

        void updateFromEngineData();

        bool hasBeenDestroyed() const;

        void advanceAnimation();

    private:
        void maskCoveredTiles();

        void revealCoveredTiles();

        void setDestroyed();
};

#endif // BUILDINGVIEW_HPP
