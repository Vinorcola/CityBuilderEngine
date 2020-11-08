#ifndef DYNAMICELEMENT_HPP
#define DYNAMICELEMENT_HPP

#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsPixmapItem>

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

        virtual QRectF boundingRect() const override;
        virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};

#endif // DYNAMICELEMENT_HPP
