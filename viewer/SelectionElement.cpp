#include "SelectionElement.hpp"





SelectionElement::SelectionElement(const QSizeF& baseTileSize) :
    QGraphicsPolygonItem(),
    baseTileSize(baseTileSize),
    goodBrush(Qt::SolidPattern),
    goodPen(),
    badBrush(Qt::SolidPattern),
    badPen(),
    currentBrush(&badBrush),
    currentPen(&badPen),
    currentArea()
{
    // Setup good brush and pen.
    QColor goodColor(0, 224, 0, 127);
    goodBrush.setColor(goodColor);
    goodPen.setColor(goodColor);
    goodPen.setJoinStyle(Qt::MiterJoin);

    // Setup bad brush and pen.
    QColor badColor(244, 0, 0, 127);
    badBrush.setColor(badColor);
    badPen.setColor(badColor);
    badPen.setJoinStyle(Qt::MiterJoin);

    setZValue(2.0);
}





void SelectionElement::setSize(const MapSize& size)
{
    currentArea = MapArea(currentArea.getLeft(), size);
    qreal sizeRatio(size.getValue());
    qreal halfBaseTileSizeHeight(baseTileSize.height() / 2.0);
    qreal halfBaseTileSizeWidth(baseTileSize.width() / 2.0);

    QPolygonF polygon;
    polygon.append(QPointF(halfBaseTileSizeWidth * sizeRatio, -halfBaseTileSizeHeight * (sizeRatio - 1.0)));
    polygon.append(QPointF(baseTileSize.width() * sizeRatio , halfBaseTileSizeHeight                     ));
    polygon.append(QPointF(halfBaseTileSizeWidth * sizeRatio, halfBaseTileSizeHeight * (sizeRatio + 1.0) ));
    polygon.append(QPointF(0                                , halfBaseTileSizeHeight                     ));
    polygon.append(polygon.first());

    setPolygon(polygon);
    refresh();
}





void SelectionElement::setGood()
{
    if (currentBrush == &badBrush)
    {
        currentBrush = &goodBrush;
        currentPen = &goodPen;
        refresh();
    }
}





void SelectionElement::setBad()
{
    if (currentBrush == &goodBrush)
    {
        currentBrush = &badBrush;
        currentPen = &badPen;
        refresh();
    }
}





void SelectionElement::attachToTile(const Tile& tile)
{
    currentArea = MapArea(tile.getCoordinates(), currentArea.getSize());
    setPos(tile.pos());
}





const MapArea& SelectionElement::getCoveredArea() const
{
    return currentArea;
}





void SelectionElement::refresh()
{
    setBrush(*currentBrush);
    setPen(*currentPen);
}
