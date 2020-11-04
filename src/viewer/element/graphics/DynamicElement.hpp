#ifndef DYNAMICELEMENT_HPP
#define DYNAMICELEMENT_HPP

#include <QtCore/QPointer>
#include <QtWidgets/QGraphicsItem>

#include "src/engine/map/MapCoordinates.hpp"

class Character;
class Image;

class DynamicElement : public QGraphicsItem
{
    private:
        const QSizeF& baseTileSize;
        QGraphicsPixmapItem imageItem;

    public:
        DynamicElement(const QSizeF& baseTileSize, const Image& elementImage, const QPointF& positionOnTile);

        void setImage(const Image& image);

        void updateLocation(const QPointF& positionOnTile);

        virtual QRectF boundingRect() const;
        virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);
};

#endif // DYNAMICELEMENT_HPP
