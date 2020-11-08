#ifndef TILE_HPP
#define TILE_HPP

#include <QtWidgets/QGraphicsObject>

#include "src/engine/map/MapCoordinates.hpp"
#include "src/defines.hpp"

class DynamicElement;
class StaticElement;

class Tile : public QGraphicsObject
{
        Q_OBJECT

    private:
        MapCoordinates location;
        QGraphicsItem* groundElement; ///< The ground nature element (grass for example).
        optional<QGraphicsItem*> staticElement; ///< The static element (building or nature element).

    public:
        Tile(const MapCoordinates& location, const QSizeF& baseTileSize, QGraphicsItem* groundElement);

        const MapCoordinates& getCoordinates() const;

        void setStaticElement(QGraphicsItem* staticElement);

        void dropStaticElement();

        void registerDynamicElement(QGraphicsItem* element);

        void moveDynamicElementTo(QGraphicsItem* element, Tile& other);

        void unregisterDynamicElement(QGraphicsItem* element);

        virtual QRectF boundingRect() const override;
        virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
        virtual QPainterPath shape() const override;

    signals:
        void isCurrentTile(Tile* tile);

    protected:
        virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
};

#endif // TILE_HPP
