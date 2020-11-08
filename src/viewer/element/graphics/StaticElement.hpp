#ifndef STATICELEMENT_HPP
#define STATICELEMENT_HPP

#include <QtWidgets/QGraphicsPixmapItem>

#include "src/defines.hpp"

class Image;
class MapSize;
class Positioning;

class StaticElement : public QGraphicsPixmapItem
{
    private:
        QPainterPath shapePath;
        optional<QGraphicsPixmapItem*> animationItem;

    public:
        StaticElement(const Positioning& positioning, const MapSize& elementSize, const Image& elementImage);

        void setAnimationImage(const Image& image);

        void dropAnimationImage();

        virtual QPainterPath shape() const;
};

#endif // STATICELEMENT_HPP
