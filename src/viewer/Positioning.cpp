#include "Positioning.hpp"

#include <cassert>
#include <QtCore/QPoint>
#include <QtCore/QPointF>
#include <QtCore/QtMath>
#include <QtGui/QPainterPath>
#include <QtGui/QPolygonF>

#include "src/engine/map/MapCoordinates.hpp"
#include "src/engine/map/MapSize.hpp"



Positioning::Positioning(const QSize& tileSize) :
    tileSizeAsFloat(tileSize.width() + 2, tileSize.height()),
    halfTileSizeAsInt(tileSize.width() / 2 + 1, tileSize.height() / 2),
    halfTileSizeAsFloat(tileSizeAsFloat.width() / 2.0, tileSizeAsFloat.height() / 2.0)
{
    // NOTE: We add 2px to tile width, which is the margin between two tiles. For half tile size, it then becomes 1px.
}



QPoint Positioning::getTilePosition(const MapCoordinates& location) const
{
    const int X(location.getX());
    const int Y(location.getY());

    return {
        (Y + X) * halfTileSizeAsInt.width(),
        (Y - X) * halfTileSizeAsInt.height(),
    };
}



QPoint Positioning::getStaticElementPositionInTile(const MapSize& elementSize, const int imageHeight) const
{
    assert(elementSize.isSquare());

    // A static element is attached to the tile located at the left corner of it's area. The height will depends on the
    // element size, since we must align it with the bottom tile of it's area.
    return {
        0,
        (elementSize.getHeight() + 1) * halfTileSizeAsInt.height() - imageHeight,
    };
}



QPoint Positioning::getStaticElementPositionInTile(const MapSize& elementSize, const int imageHeight, const QPoint& tileOffset) const
{
    assert(elementSize.isSquare());

    // A static element is attached to the tile located at the left corner of it's area. But we have to apply the given
    // offset before our calculations. The height will depends on the element size, since we must align it with the
    // bottom tile of it's area.
    int xOffset((tileOffset.x() + tileOffset.y()) * halfTileSizeAsInt.width());
    int yOffset(- (tileOffset.x() - tileOffset.y()) * halfTileSizeAsInt.height());

    return {
        xOffset,
        yOffset + (elementSize.getHeight() + 1) * halfTileSizeAsInt.height() - imageHeight,
    };
}



QPainterPath Positioning::getTileAreaPainterPath(const MapSize& areaSize) const
{
    const qreal WIDTH_RATIO(areaSize.getWidth());
    const qreal HEIGHT_RATIO(areaSize.getHeight());

    QPainterPath path;
    path.moveTo(
        // Left corner
        -1.0,
        halfTileSizeAsFloat.height()
    );
    path.lineTo(
        // Top corner
        WIDTH_RATIO * halfTileSizeAsFloat.width() - 1.0,
        -(WIDTH_RATIO - 1.0) * halfTileSizeAsFloat.height()
    );
    path.lineTo(
        // Right corner
        (HEIGHT_RATIO + WIDTH_RATIO) * halfTileSizeAsFloat.width() - 1.0,
        (HEIGHT_RATIO - WIDTH_RATIO + 1.0) * halfTileSizeAsFloat.height()
    );
    path.lineTo(
        // Bottom corner
        HEIGHT_RATIO * halfTileSizeAsFloat.width() - 1.0,
        (HEIGHT_RATIO + 1.0) * halfTileSizeAsFloat.height()
    );
    path.closeSubpath();

    return path;
}



QPolygonF Positioning::getTileAreaPolygon(const MapSize& areaSize) const
{
    const qreal WIDTH_RATIO(areaSize.getWidth());
    const qreal HEIGHT_RATIO(areaSize.getHeight());

    QPolygonF polygon;
    polygon.append(QPointF(
        // Left corner
        -1.0,
        halfTileSizeAsFloat.height()
    ));
    polygon.append(QPointF(
        // Top corner
        WIDTH_RATIO * halfTileSizeAsFloat.width() - 1.0,
        -(WIDTH_RATIO - 1.0) * halfTileSizeAsFloat.height()
    ));
    polygon.append(QPointF(
        // Right corner
        (HEIGHT_RATIO + WIDTH_RATIO) * halfTileSizeAsFloat.width() - 1.0,
        (HEIGHT_RATIO - WIDTH_RATIO + 1.0) * halfTileSizeAsFloat.height()
    ));
    polygon.append(QPointF(
        // Bottom corner
        HEIGHT_RATIO * halfTileSizeAsFloat.width() - 1.0,
        (HEIGHT_RATIO + 1.0) * halfTileSizeAsFloat.height()
    ));
    polygon.append(polygon.first());

    return polygon;
}



QRectF Positioning::getBoundingRect(const MapSize& areaSize) const
{
    const qreal WIDTH_RATIO(areaSize.getWidth());
    const qreal HEIGHT_RATIO(areaSize.getHeight());

    return {
        QPointF(
            -1.0, // Left corner X
            -(WIDTH_RATIO - 1.0) * halfTileSizeAsFloat.height() // Top corner Y
        ),
        QPointF(
            (HEIGHT_RATIO + WIDTH_RATIO) * halfTileSizeAsFloat.width() - 1.0, // Right corner X
            (HEIGHT_RATIO + 1.0) * halfTileSizeAsFloat.height() // Bottom corner Y
        ),
    };
}



QPointF Positioning::getDynamicElementPositionInTile(const MapCoordinates& elementLocation) const
{
    const auto TILE_COORDINATES(elementLocation.getRounded());
    const qreal X_DIFF(elementLocation.getX() - TILE_COORDINATES.getX());
    const qreal Y_DIFF(elementLocation.getY() - TILE_COORDINATES.getY());

    return {
        X_DIFF * tileSizeAsFloat.width() / 2.0 + Y_DIFF * tileSizeAsFloat.width() / 2.0,
        -X_DIFF * tileSizeAsFloat.height() / 2.0 + Y_DIFF * tileSizeAsFloat.height() / 2.0,
    };
}



MapCoordinates Positioning::getMapCoordinatesFromMouseCoordinates(const QPointF& mouseCoordinates) const
{
    const int X(qFloor(mouseCoordinates.x() / 2.0));
    const int Y(qFloor(mouseCoordinates.y()));

    return {
        qFloor(static_cast<qreal>(X - Y + halfTileSizeAsInt.height()) / 30.0),
        qFloor(static_cast<qreal>(X + Y + halfTileSizeAsInt.height() + 1) / 30.0) - 1,
    };
}
