#include "Positioning.hpp"

#include <QtCore/QPoint>
#include <QtCore/QPointF>
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
    // A static element is attached to the tile located at the left corner of it's area. The height will depends on the
    // element size, since we must align it with the bottom tile of it's area.
    return {
        0,
        (elementSize.getValue() + 1) * halfTileSize.height() - imageHeight,
    };
}



QPainterPath Positioning::getTileAreaPainterPath(const MapSize& areaSize) const
{
    const qreal SIZE_RATIO(areaSize.getValue());

    QPainterPath path;
    path.moveTo(-1.0                                           , halfTileSize.height()                      ); // Left corner
    path.lineTo(SIZE_RATIO * (1.0 + halfTileSize.width()) - 1.0, -(SIZE_RATIO - 1.0) * halfTileSize.height()); // Top corner
    path.lineTo(SIZE_RATIO * (2.0 + tileSize.width()) - 1.0    , halfTileSize.height()                      ); // Right corner
    path.lineTo(SIZE_RATIO * (1.0 + halfTileSize.width()) - 1.0, (SIZE_RATIO + 1.0) * halfTileSize.height() ); // Bottom corner
    path.closeSubpath();

    return path;
}



QPolygonF Positioning::getTileAreaPolygon(const MapSize& areaSize) const
{
    const qreal SIZE_RATIO(areaSize.getValue());

    QPolygonF polygon;
    polygon.append(QPointF(-1.0                                           , halfTileSize.height()                      )); // Left corner
    polygon.append(QPointF(SIZE_RATIO * (1.0 + halfTileSize.width()) - 1.0, -(SIZE_RATIO - 1.0) * halfTileSize.height())); // Top corner
    polygon.append(QPointF(SIZE_RATIO * (2.0 + tileSize.width()) - 1.0    , halfTileSize.height()                      )); // Right corner
    polygon.append(QPointF(SIZE_RATIO * (1.0 + halfTileSize.width()) - 1.0, (SIZE_RATIO + 1.0) * halfTileSize.height() )); // Bottom corner
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
