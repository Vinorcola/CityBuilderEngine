#ifndef DYNAMICELEMENT_HPP
#define DYNAMICELEMENT_HPP

#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsPixmapItem>

class Image;
class MapCoordinates;
class Positioning;

class DynamicElement : public QGraphicsItem
{
    private:
        QGraphicsPixmapItem imageItem;

    public:
        DynamicElement(const Positioning& positioning, const Image& elementImage, const MapCoordinates& location);

        void setImage(const Image& image);

        void updateLocation(const QPointF& positionOnTile);

        virtual QRectF boundingRect() const override;
        virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};

#endif // DYNAMICELEMENT_HPP
