#include "ConstructionCursor.hpp"

#include <QtGui/QPen>
#include <QtWidgets/QGraphicsSceneMouseEvent>

#include "src/viewer/construction/AreaChecker.hpp"
#include "src/viewer/image/BuildingImage.hpp"
#include "src/viewer/image/ImageLibrary.hpp"



ConstructionCursor::ConstructionCursor(
    const QSizeF& baseTileSize,
    const AreaChecker& areaChecker,
    const BuildingImage& buildingImage,
    const MapSize& buildingSize
) :
    QGraphicsObject(),
    baseTileSize(baseTileSize),
    areaChecker(areaChecker),
    coveredArea({0, 0}, buildingSize),
    buildingImage(buildingImage.getConstructionImage().getPixmap(), this),
    forbiddenAreaImage(this)
{
    const qreal sizeRatio(buildingSize.getValue());
    const qreal halfBaseTileSizeHeight(baseTileSize.height() / 2.0);
    const qreal halfBaseTileSizeWidth(1.0 + baseTileSize.width() / 2.0);

    this->buildingImage.setPos(0, (sizeRatio + 1.0) * halfBaseTileSizeHeight - this->buildingImage.pixmap().height());

    QPolygonF polygon;
    polygon.append(QPointF(-1.0                                    , halfBaseTileSizeHeight                     )); // Left corner
    polygon.append(QPointF(sizeRatio * halfBaseTileSizeWidth - 1.0 , -(sizeRatio - 1.0) * halfBaseTileSizeHeight)); // Top corner
    polygon.append(QPointF(sizeRatio * (2.0 + baseTileSize.width()), halfBaseTileSizeHeight                     )); // Right corner
    polygon.append(QPointF(sizeRatio * halfBaseTileSizeWidth - 1.0 , (sizeRatio + 1.0) * halfBaseTileSizeHeight )); // Bottom corner
    polygon.append(polygon.first());
    forbiddenAreaImage.setPolygon(polygon);
    forbiddenAreaImage.setPen(Qt::NoPen);
    forbiddenAreaImage.setBrush(ImageLibrary::RED_BRUSH);

    setZValue(2.0);
    setVisible(false);
}



const MapArea& ConstructionCursor::getCoveredArea() const
{
    return coveredArea;
}



void ConstructionCursor::displayAtLocation(const MapCoordinates& location)
{
    setVisible(true);
    setPos(
        (location.getY() + location.getX()) * (1.0 + baseTileSize.width() / 2.0),
        (location.getY() - location.getX()) * baseTileSize.height() / 2.0
    );

    coveredArea.moveTo(location);

    isCoveredAreaFree = areaChecker.isConstructible(coveredArea);
    buildingImage.setVisible(isCoveredAreaFree);
    forbiddenAreaImage.setVisible(!isCoveredAreaFree);
}



void ConstructionCursor::refresh()
{
    isCoveredAreaFree = areaChecker.isConstructible(coveredArea);
    buildingImage.setVisible(isCoveredAreaFree);
    forbiddenAreaImage.setVisible(!isCoveredAreaFree);
}



QRectF ConstructionCursor::boundingRect() const
{
    return buildingImage.boundingRect();
}



void ConstructionCursor::paint(QPainter* /*painter*/, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{

}



void ConstructionCursor::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    event->accept();
}



void ConstructionCursor::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    switch (event->button()) {
        case Qt::LeftButton:
            if (isCoveredAreaFree) {
                emit construct(coveredArea);
            }
            break;

        case Qt::RightButton:
            emit cancel();
            break;

        default:
            break;
    }
}
