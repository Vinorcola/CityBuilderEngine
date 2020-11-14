#include "ConstructionCursor.hpp"

#include <QtGui/QPen>
#include <QtWidgets/QGraphicsSceneMouseEvent>

#include "src/viewer/construction/AreaCheckerInterface.hpp"
#include "src/viewer/construction/RoadPathGeneratorInterface.hpp"
#include "src/viewer/image/BuildingImage.hpp"
#include "src/viewer/image/ImageLibrary.hpp"
#include "src/viewer/Positioning.hpp"



ConstructionCursor::Cursor::Cursor(
    QGraphicsItem* parent,
    const Positioning& positioning,
    const BuildingImage& buildingImage,
    const MapSize& buildingSize
) :
    QGraphicsItem(parent),
    buildingGraphics(buildingImage.getConstructionImage().getPixmap(), this),
    forbiddenAreaGraphics(this)
{
    buildingGraphics.setPos(positioning.getStaticElementPositionInTile(buildingSize, this->buildingGraphics.pixmap().height()));

    forbiddenAreaGraphics.setPolygon(positioning.getTileAreaPolygon(buildingSize));
    forbiddenAreaGraphics.setPen(Qt::NoPen);
    forbiddenAreaGraphics.setBrush(ImageLibrary::RED_BRUSH);

    setZValue(2.0);
}



void ConstructionCursor::Cursor::updateStatus(bool isCoveredAreaFree)
{
    buildingGraphics.setVisible(isCoveredAreaFree);
    forbiddenAreaGraphics.setVisible(!isCoveredAreaFree);
}



QRectF ConstructionCursor::Cursor::boundingRect() const
{
    return buildingGraphics.boundingRect();
}



void ConstructionCursor::Cursor::paint(QPainter* /*painter*/, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{

}



ConstructionCursor::RoadPath::RoadPath(
    const Positioning& positioning,
    QGraphicsItem* parent,
    const MapCoordinates& origin,
    const QPixmap& image
) :
    positioning(positioning),
    parent(parent),
    image(image),
    origin(origin),
    path(),
    graphics()
{

}



ConstructionCursor::RoadPath::~RoadPath()
{
    qDeleteAll(graphics);
}



void ConstructionCursor::RoadPath::refreshPath(const QList<MapCoordinates>& path)
{
    resetPath();
    for (auto coordinates : path) {
        this->path.append(MapArea(coordinates));
        auto roadItem(new QGraphicsPixmapItem(image, parent));
        auto position(positioning.getTilePosition(coordinates));
        roadItem->setPos(position);
        graphics.append(roadItem);
    }
}



const MapCoordinates& ConstructionCursor::RoadPath::getOrigin() const
{
    return origin;
}



const QList<MapArea>& ConstructionCursor::RoadPath::getPath() const
{
    return path;
}



void ConstructionCursor::RoadPath::resetPath()
{
    path.clear();
    qDeleteAll(graphics);
    graphics.clear();
}



ConstructionCursor::ConstructionCursor(
    const Positioning& positioning,
    const AreaCheckerInterface& areaChecker,
    const RoadPathGeneratorInterface& roadPathGenerator,
    const BuildingInformation& buildingConf,
    const BuildingImage& buildingImage
) :
    QGraphicsObject(),
    positioning(positioning),
    areaChecker(areaChecker),
    roadPathGenerator(roadPathGenerator),
    buildingConf(buildingConf),
    buildingImage(buildingImage),
    selectionType(buildingConf.getType() == BuildingInformation::Type::Road ? SelectionType::Road : SelectionType::Single),
    coveredArea({0, 0}, buildingConf.getSize()),
    cursor(this, positioning, buildingImage, buildingConf.getSize()),
    roadPath(nullptr)
{
    setVisible(false);
}



ConstructionCursor::~ConstructionCursor()
{
    if (roadPath) {
        delete roadPath;
    }
}



const MapArea& ConstructionCursor::getCoveredArea() const
{
    return coveredArea;
}



void ConstructionCursor::displayAtLocation(const MapCoordinates& location)
{
    setVisible(true);
    cursor.setPos(positioning.getTilePosition(location));

    coveredArea.moveTo(location);

    // TODO: Handle road construction for checking area.
    isCoveredAreaFree = areaChecker.isConstructible(coveredArea);
    cursor.updateStatus(isCoveredAreaFree);

    if (roadPath) {
        roadPath->refreshPath(roadPathGenerator.getShortestPathForRoad(roadPath->getOrigin(), location));
    }
}



void ConstructionCursor::refresh()
{
    isCoveredAreaFree = areaChecker.isConstructible(coveredArea);
    cursor.updateStatus(isCoveredAreaFree);
}



QRectF ConstructionCursor::boundingRect() const
{
    // Translate cursor bouding rect to it's position.
    auto cursorBoundingRect(cursor.boundingRect());

    return {
        cursor.pos().x() + cursorBoundingRect.x(),
        cursor.pos().y() + cursorBoundingRect.y(),
        cursorBoundingRect.width(),
        cursorBoundingRect.height(),
    };
}



void ConstructionCursor::paint(QPainter* /*painter*/, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{

}



void ConstructionCursor::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    event->accept();
    if (selectionType == SelectionType::Road) {
        roadPath = new RoadPath(positioning, this, coveredArea.getLeft(), buildingImage.getInactiveImage().getPixmap());
    }
}



void ConstructionCursor::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    switch (event->button()) {
        case Qt::LeftButton:
            if (isCoveredAreaFree) {
                switch (selectionType) {
                    case SelectionType::Road:
                        if (roadPath) {
                            emit construct(buildingConf, roadPath->getPath());
                            delete roadPath;
                            roadPath = nullptr;
                        }
                        break;

                    case SelectionType::Single:
                        emit construct(buildingConf, {coveredArea});
                        break;
                }
            }
            break;

        case Qt::RightButton:
            if (roadPath) {
                delete roadPath;
                roadPath = nullptr;
            }
            emit cancel();
            break;

        default:
            break;
    }
}
