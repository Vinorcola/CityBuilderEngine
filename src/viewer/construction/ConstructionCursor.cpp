#include "ConstructionCursor.hpp"

#include <QtGui/QPen>
#include <QtWidgets/QGraphicsSceneMouseEvent>

#include "src/viewer/construction/AreaChecker.hpp"
#include "src/viewer/image/BuildingImage.hpp"
#include "src/viewer/image/ImageLibrary.hpp"
#include "src/viewer/Positioning.hpp"



ConstructionCursor::ConstructionCursor(
    const Positioning& positioning,
    const AreaChecker& areaChecker,
    const BuildingImage& buildingImage,
    const MapSize& buildingSize
) :
    QGraphicsObject(),
    positioning(positioning),
    areaChecker(areaChecker),
    coveredArea({0, 0}, buildingSize),
    buildingImage(buildingImage.getConstructionImage().getPixmap(), this),
    forbiddenAreaImage(this)
{
    this->buildingImage.setPos(positioning.getStaticElementPositionInTile(buildingSize, this->buildingImage.pixmap().height()));

    forbiddenAreaImage.setPolygon(positioning.getTileAreaPolygon(buildingSize));
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
    setPos(positioning.getTilePosition(location));

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
