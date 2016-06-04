#include "SelectionElement.hpp"





SelectionElement::SelectionElement(const QSizeF& baseTileSize) :
    QGraphicsPolygonItem(),
    baseTileSize(baseTileSize),
    goodBrush(Qt::SolidPattern),
    goodPen()
{
    // Setup good brush and pen.
    QColor goodColor(0, 224, 0, 127);
    goodBrush.setColor(goodColor);
    goodPen.setColor(goodColor);
    goodPen.setJoinStyle(Qt::MiterJoin);

    setZValue(2.0);
}





void SelectionElement::setSize(const MapSize& size)
{
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
    setBrush(goodBrush);
    setPen(goodPen);
}
