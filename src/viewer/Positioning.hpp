#ifndef POSITIONING_HPP
#define POSITIONING_HPP

#include <QtCore/QSize>
#include <QtCore/QSizeF>

class MapCoordinates;
class MapSize;
class QPainterPath;
class QPoint;
class QPointF;
class QPolygonF;

/**
 * @brief A class for calculating any positioning of graphical elements.
 */
class Positioning
{
    private:
        const QSize& tileSize;
        const QSizeF tileRealSize;
        const QSize halfTileSize;

    public:
        explicit Positioning(const QSize& tileSize);

        /**
         * @brief Get the tile position on the map.
         */
        QPoint getTilePosition(const MapCoordinates& location) const;

        /**
         * @brief Get the position of a static element within a tile.
         */
        QPoint getStaticElementPositionInTile(const MapSize& elementSize, const int imageHeight) const;
        /**
         * @brief Get the painter path for a tile area.
         */
        QPainterPath getTileAreaPainterPath(const MapSize& areaSize) const;
        /**
         * @brief Get the polygon for a tile area.
         */
        QPolygonF getTileAreaPolygon(const MapSize& areaSize) const;

        /**
         * @brief Get the position of a dynamic element withint a tile.
         */
        QPointF getDynamicElementPositionInTile(const MapCoordinates& elementLocation) const;

        MapCoordinates getMapCoordinatesFromMouseCoordinates(const QPointF& mouseCoordinates) const;
};

#endif // POSITIONING_HPP
