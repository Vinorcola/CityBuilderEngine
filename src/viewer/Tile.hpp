#ifndef TILE_HPP
#define TILE_HPP

#include <QtCore/QList>
#include <QtCore/QStack>
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
        QGraphicsItem* groundElement;///< The ground nature element (grass for example).
        optional<QGraphicsItem*> staticElement;///< The static element (building or nature element).
        QList<DynamicElement*> dynamicElementList;

    public:
        Tile(const MapCoordinates& location, const QSizeF& baseTileSize, QGraphicsItem* groundElement);

        const MapCoordinates& getCoordinates() const;

        void setStaticElement(QGraphicsItem* staticElement);

        void dropStaticElement();

        void registerDynamicElement(DynamicElement* element);

        void unregisterDynamicElement(DynamicElement* element);

        virtual QRectF boundingRect() const;
        virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);
        virtual QPainterPath shape() const;

    signals:
        void isCurrentTile(Tile* tile);

    protected:
        virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
};

#endif // TILE_HPP
