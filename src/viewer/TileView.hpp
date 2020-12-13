#ifndef TILEVIEW_HPP
#define TILEVIEW_HPP

#include <QtWidgets/QGraphicsItem>

#include "src/engine/map/MapCoordinates.hpp"
#include "src/defines.hpp"

class DynamicElement;
class Positioning;
class StaticElement;

/**
 * @brief Display a tile on the map.
 *
 * The tile will hold a nature element, optionaly a building and several characters.
 */
class TileView : public QGraphicsItem
{
    private:
        MapCoordinates location;
        QGraphicsItem& groundElement; ///< The ground nature element (grass for example).
        optional<QGraphicsItem*> staticElement; ///< The static element (building or nature element).

    public:
        TileView(const Positioning& positioning, const MapCoordinates& location, QGraphicsItem& groundElement);

        const MapCoordinates& getCoordinates() const;

        void setStaticElement(QGraphicsItem* staticElement);
        void dropStaticElement();

        void registerDynamicElement(QGraphicsItem* element);
        void moveDynamicElementTo(QGraphicsItem* element, TileView& other);
        void unregisterDynamicElement(QGraphicsItem* element);

        virtual QRectF boundingRect() const override;
        virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
        virtual QPainterPath shape() const override;
};

#endif // TILEVIEW_HPP
