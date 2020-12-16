#include "Positioning.hpp"

#include <cassert>
#include <QtCore/QPoint>
#include <QtCore/QPointF>
#include <QtCore/QtMath>
#include <QtGui/QPainterPath>
#include <QtGui/QPolygonF>

#include "src/global/geometry/DynamicElementCoordinates.hpp"
#include "src/global/geometry/TileAreaSize.hpp"
#include "src/global/geometry/TileCoordinates.hpp"



Positioning::Positioning(const QSize& tileSize) :
    tileSizeAsFloat(tileSize.width() + 2, tileSize.height()),
    halfTileSizeAsInt(tileSize.width() / 2 + 1, tileSize.height() / 2),
    halfTileSizeAsFloat(tileSizeAsFloat.width() / 2.0, tileSizeAsFloat.height() / 2.0)
{
    // NOTE: We add 2px to tile width, which is the margin between two tiles. For half tile size, it then becomes 1px.
}



QPoint Positioning::getTilePosition(const TileCoordinates& location) const
{
    return {
        (location.y() + location.x()) * halfTileSizeAsInt.width(),
        (location.y() - location.x()) * halfTileSizeAsInt.height(),
    };
}



QPoint Positioning::getStaticElementPositionInTile(const TileAreaSize& elementSize, const int imageHeight) const
{
    assert(elementSize.isSquare());

    // A static element is attached to the tile located at the left corner of it's area. The height will depends on the
    // element size, since we must align it with the bottom tile of it's area.
    return {
        0,
        (elementSize.width() + 1) * halfTileSizeAsInt.height() - imageHeight,
    };
}



QPoint Positioning::getStaticElementPositionInTile(
    const TileAreaSize& elementSize,
    const int imageHeight,
    const QPoint& tileOffset
) const {

    assert(elementSize.isSquare());

    // A static element is attached to the tile located at the left corner of it's area. But we have to apply the given
    // offset before our calculations. The height will depends on the element size, since we must align it with the
    // bottom tile of it's area.
    int xOffset((tileOffset.x() + tileOffset.y()) * halfTileSizeAsInt.width());
    int yOffset(- (tileOffset.x() - tileOffset.y()) * halfTileSizeAsInt.height());

    return {
        xOffset,
        yOffset + (elementSize.width() + 1) * halfTileSizeAsInt.height() - imageHeight,
    };
}



QPainterPath Positioning::getTileAreaPainterPath(const TileAreaSize& areaSize) const
{
    const qreal WIDTH_RATIO(areaSize.width());
    const qreal HEIGHT_RATIO(areaSize.height());

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



QPolygonF Positioning::getTileAreaPolygon(const TileAreaSize& areaSize) const
{
    const qreal WIDTH_RATIO(areaSize.width());
    const qreal HEIGHT_RATIO(areaSize.height());

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



QRectF Positioning::getBoundingRect(const TileAreaSize& areaSize) const
{
    const qreal WIDTH_RATIO(areaSize.width());
    const qreal HEIGHT_RATIO(areaSize.height());

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



QPointF Positioning::getDynamicElementPositionInTile(const DynamicElementCoordinates& elementLocation) const
{
    const auto TILE_COORDINATES(elementLocation.associatedTileCoordinates());
    const qreal X_DIFF(elementLocation.x() - static_cast<qreal>(TILE_COORDINATES.x()));
    const qreal Y_DIFF(elementLocation.y() - static_cast<qreal>(TILE_COORDINATES.y()));

    return {
        X_DIFF * tileSizeAsFloat.width() / 2.0 + Y_DIFF * tileSizeAsFloat.width() / 2.0,
        -X_DIFF * tileSizeAsFloat.height() / 2.0 + Y_DIFF * tileSizeAsFloat.height() / 2.0,
    };
}



TileCoordinates Positioning::getTileCoordinatesFromMouseCoordinates(const QPointF& mouseCoordinates) const
{
    const int X(qFloor(mouseCoordinates.x() / 2.0));
    const int Y(qFloor(mouseCoordinates.y()));

    return {
        qFloor(static_cast<qreal>(X - Y + halfTileSizeAsInt.height()) / 30.0),
        qFloor(static_cast<qreal>(X + Y + halfTileSizeAsInt.height() + 1) / 30.0) - 1,
    };
}
