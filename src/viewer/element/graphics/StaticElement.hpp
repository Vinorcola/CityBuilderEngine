#ifndef STATICELEMENT_HPP
#define STATICELEMENT_HPP

#include <QtWidgets/QGraphicsPixmapItem>

#include "src/defines.hpp"

class Image;
class Positioning;
class TileAreaSize;

class StaticElement : public QGraphicsPixmapItem
{
    private:
        QPainterPath shapePath;
        optional<QGraphicsPixmapItem*> animationItem;

    public:
        StaticElement(const Positioning& positioning, const TileAreaSize& elementSize, const Image& elementImage);

        void setAnimationImage(const Image& image);
        void dropAnimationImage();

        virtual QPainterPath shape() const override;
};

#endif // STATICELEMENT_HPP
