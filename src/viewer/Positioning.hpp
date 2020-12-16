#ifndef POSITIONING_HPP
#define POSITIONING_HPP

#include <QtCore/QSize>
#include <QtCore/QSizeF>

class DynamicElementCoordinates;
class QPainterPath;
class QPoint;
class QPointF;
class QPolygonF;
class QRectF;
class TileAreaSize;
class TileCoordinates;

/**
 * @brief A class for calculating any positioning of graphical elements.
 */
class Positioning
{
    private:
        const QSizeF tileSizeAsFloat;
        const QSize halfTileSizeAsInt;
        const QSizeF halfTileSizeAsFloat;

    public:
        explicit Positioning(const QSize& tileSize);

        /**
         * @brief Get the tile position on the map.
         */
        QPoint getTilePosition(const TileCoordinates& location) const;

        /**
         * @brief Get the position of a static element within a tile.
         */
        QPoint getStaticElementPositionInTile(const TileAreaSize& elementSize, const int imageHeight) const;
        /**
         * @brief Get the position of a static element within a tile and applying a tile offset (for construction cursor exclusively).
         */
        QPoint getStaticElementPositionInTile(const TileAreaSize& elementSize, const int imageHeight, const QPoint& tileOffset) const;
        /**
         * @brief Get the painter path for a tile area.
         */
        QPainterPath getTileAreaPainterPath(const TileAreaSize& areaSize) const;
        /**
         * @brief Get the polygon for a tile area.
         */
        QPolygonF getTileAreaPolygon(const TileAreaSize& areaSize) const;
        /**
         * @brief Get the bounding rect of a static element.
         */
        QRectF getBoundingRect(const TileAreaSize& areaSize) const;

        /**
         * @brief Get the position of a dynamic element withint a tile.
         */
        QPointF getDynamicElementPositionInTile(const DynamicElementCoordinates& elementLocation) const;

        TileCoordinates getTileCoordinatesFromMouseCoordinates(const QPointF& mouseCoordinates) const;
};

#endif // POSITIONING_HPP
