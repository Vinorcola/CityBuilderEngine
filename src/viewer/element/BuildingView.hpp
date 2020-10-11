#ifndef BUILDINGVIEW_HPP
#define BUILDINGVIEW_HPP

#include <QtCore/QSharedPointer>
#include <QtCore/QSize>
#include <QtCore/QWeakPointer>

class Building;
class BuildingImage;
class ImageLibrary;
class StaticElement;
class Tile;

class BuildingView
{
    private:
        const QSize& baseTileSize;
        QWeakPointer<const Building> engineData;
        Tile& tile;
        BuildingImage& image;
        StaticElement* graphicElement;
        int currentViewVersion;
        int animationIndex;

    public:
        BuildingView(
            ImageLibrary& imageLibrary,
            const QSize& baseTileSize,
            const QSharedPointer<const Building>& engineData,
            Tile& tile
        );

        ~BuildingView();

        void updateFromEngineData();

        bool hasBeenDestroyed() const;

        void advanceAnimation();

    private:
        void setDestroyed();
};

#endif // BUILDINGVIEW_HPP
