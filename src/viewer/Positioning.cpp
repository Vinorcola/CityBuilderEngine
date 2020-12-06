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
    tileSize(tileSize),
    tileRealSize(tileSize),
    halfTileSize(tileSize.width() / 2, tileSize.height() / 2)
{

}



QPoint Positioning::getTilePosition(const MapCoordinates& location) const
{
    const int X(location.getX());
    const int Y(location.getY());

    return {
        (Y + X) * (1 + halfTileSize.width()),
        (Y - X) * halfTileSize.height(),
    };
}



QPoint Positioning::getStaticElementPositionInTile(const MapSize& elementSize, const int imageHeight) const
{
    assert(elementSize.isSquare());

    // A static element is attached to the tile located at the left corner of it's area. The height will depends on the
    // element size, since we must align it with the bottom tile of it's area.
    return {
        0,
        (elementSize.getHeight() + 1) * halfTileSize.height() - imageHeight,
    };
}



QPainterPath Positioning::getTileAreaPainterPath(const MapSize& areaSize) const
{
    const qreal WIDTH_RATIO(areaSize.getWidth());
    const qreal HEIGHT_RATIO(areaSize.getHeight());

    QPainterPath path;
    path.moveTo(-1.0                                            , halfTileSize.height()                       ); // Left corner
    path.lineTo(WIDTH_RATIO * (1.0 + halfTileSize.width()) - 1.0, -(WIDTH_RATIO - 1.0) * halfTileSize.height()); // Top corner
    path.lineTo(HEIGHT_RATIO * (2.0 + tileSize.width()) - 1.0   , halfTileSize.height()                       ); // Right corner
    path.lineTo(WIDTH_RATIO * (1.0 + halfTileSize.width()) - 1.0, (WIDTH_RATIO + 1.0) * halfTileSize.height() ); // Bottom corner
    path.closeSubpath();

    return path;
}



QPolygonF Positioning::getTileAreaPolygon(const MapSize& areaSize) const
{
    const qreal WIDTH_RATIO(areaSize.getWidth());
    const qreal HEIGHT_RATIO(areaSize.getHeight());

    QPolygonF polygon;
    polygon.append(QPointF(-1.0                                            , halfTileSize.height()                       )); // Left corner
    polygon.append(QPointF(WIDTH_RATIO * (1.0 + halfTileSize.width()) - 1.0, -(WIDTH_RATIO - 1.0) * halfTileSize.height())); // Top corner
    polygon.append(QPointF(HEIGHT_RATIO * (2.0 + tileSize.width()) - 1.0   , halfTileSize.height()                       )); // Right corner
    polygon.append(QPointF(WIDTH_RATIO * (1.0 + halfTileSize.width()) - 1.0, (WIDTH_RATIO + 1.0) * halfTileSize.height() )); // Bottom corner
    polygon.append(polygon.first());

    return polygon;
}



QPointF Positioning::getDynamicElementPositionInTile(const MapCoordinates& elementLocation) const
{
    const auto TILE_COORDINATES(elementLocation.getRounded());
    const qreal X_DIFF(elementLocation.getX() - TILE_COORDINATES.getX());
    const qreal Y_DIFF(elementLocation.getY() - TILE_COORDINATES.getY());

    return {
        X_DIFF * tileRealSize.width() / 2.0 + Y_DIFF * tileRealSize.width() / 2.0,
        -X_DIFF * tileRealSize.height() / 2.0 + Y_DIFF * tileRealSize.height() / 2.0,
    };
}



MapCoordinates Positioning::getMapCoordinatesFromMouseCoordinates(const QPointF& mouseCoordinates) const
{
    const int X(qFloor(mouseCoordinates.x() / 2.0));
    const int Y(qFloor(mouseCoordinates.y()));

    return {
        qFloor(static_cast<qreal>(X - Y + halfTileSize.height()) / 30.0),
        qFloor(static_cast<qreal>(X + Y + halfTileSize.height() + 1) / 30.0) - 1,
    };
}
