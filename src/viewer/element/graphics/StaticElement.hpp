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
        QPainterPath shapePath;
        optional<QGraphicsPixmapItem*> animationItem;

    public:
        StaticElement(const QSizeF& baseTileSize, const MapSize& elementSize, const QPixmap& elementImage);

        void setAnimationImage(const QPixmap& image, const QPoint& anchor);

        void dropAnimationImage();

        virtual QPainterPath shape() const;
};

#endif // STATICELEMENT_HPP
