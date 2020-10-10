#ifndef STATICELEMENT_HPP
#define STATICELEMENT_HPP

#include <QtWidgets/QGraphicsPixmapItem>

#include "src/engine/map/MapSize.hpp"
#include "src/defines.hpp"

class BuildingImage;
class NatureElementImage;

class StaticElement : public QGraphicsPixmapItem
{
    private:
        optional<BuildingImage*> buildingImage;
        optional<NatureElementImage*> natureElementImage;
        QPainterPath shapePath;
        optional<QGraphicsPixmapItem*> animationPixmap;

    public:
        StaticElement(const QSizeF& baseTileSize, const MapSize& elementSize, BuildingImage& buildingImage);

        StaticElement(const QSizeF& baseTileSize, const MapSize& elementSize, NatureElementImage& natureElementImage);

        virtual QPainterPath shape() const;

    private:
        StaticElement(const QSizeF& baseTileSize, const MapSize& elementSize, const QPixmap& elementImage);
};

#endif // STATICELEMENT_HPP
