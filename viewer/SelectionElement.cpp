#include "SelectionElement.hpp"

#include <QGraphicsSceneMouseEvent>

#include "global/conf/StaticElementInformation.hpp"
#include "viewer/MapScene.hpp"
#include "viewer/Tile.hpp"



SelectionElement::SelectionElement(const QSizeF& baseTileSize) :
    QGraphicsPolygonItem(),
    baseTileSize(baseTileSize),
    goodBrush(Qt::SolidPattern),
    goodPen(),
    badBrush(Qt::SolidPattern),
    badPen(),
    currentBrush(&badBrush),
    currentPen(&badPen),
    currentArea(),
    currentElementConf(nullptr)
{
    // NOTE: Changing accepted mouse buttons can affect mouse event handler mousePressEvent() and mouseReleaseEvent().
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);

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

    setVisible(false);
    setZValue(2.0);
}



void SelectionElement::setBuildingType(const StaticElementInformation* elementConf)
{
    this->currentElementConf = elementConf;
    setVisible(true);
    setSize(elementConf->getSize());
}



void SelectionElement::setGood()
{
    if (currentBrush == &badBrush) {
        currentBrush = &goodBrush;
        currentPen = &goodPen;
        refresh();
    }
}



void SelectionElement::setBad()
{
    if (currentBrush == &goodBrush) {
        currentBrush = &badBrush;
        currentPen = &badPen;
        refresh();
    }
}



void SelectionElement::hide()
{
    currentElementConf = nullptr;
    setVisible(false);
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



void SelectionElement::refresh()
{
    setBrush(*currentBrush);
    setPen(*currentPen);
}



void SelectionElement::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    // NOTE: Nothing to do here. Action only operate on mouse release event. However, we ignore the event if the element
    // is not visible. This will prevent triggering further events related to this mouse click.

    if (!isVisible()) {
        event->ignore();
    }
}



void SelectionElement::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    // NOTE: Button can be either Qt::LeftButton or Qt::RightButton because of accepted events set in constructor.
    if (event->button() == Qt::LeftButton) {
        static_cast<MapScene*>(scene())->requestBuildingCreation(currentElementConf, currentArea);
    } else {
        // Right click.
        hide();
    }
}
