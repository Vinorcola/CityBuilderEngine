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
class StaticElement;
class Tile;
class TileLocatorInterface;

class BuildingView
{
    private:
        const TileLocatorInterface& tileLocator;
        QWeakPointer<const Building> engineData;
        const MapSize& buildingSize;
        Tile& tile;
        BuildingImage& image;
        owner<StaticElement*> graphicElement;
        int currentViewVersion;
        int animationIndex;

    public:
        BuildingView(
            const TileLocatorInterface& tileLocator,
            const ImageLibrary& imageLibrary,
            const QSizeF& baseTileSize,
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
