#include "ConstructionCursor.hpp"

#include <QtGui/QPen>
#include <QtWidgets/QGraphicsSceneMouseEvent>

#include "src/global/conf/BuildingInformation.hpp"
#include "src/viewer/construction/AreaCheckerInterface.hpp"
#include "src/viewer/construction/RoadPathGeneratorInterface.hpp"
#include "src/viewer/image/BuildingAreaPartImage.hpp"
#include "src/viewer/image/BuildingImage.hpp"
#include "src/viewer/image/ImageLibrary.hpp"
#include "src/viewer/Positioning.hpp"



ConstructionCursor::Cursor::Cursor(
    QGraphicsItem* parent,
    const Positioning& positioning,
    Direction orientation,
    const QList<const BuildingAreaInformation::AreaPart*>& areaInformation,
    const BuildingImage& buildingImage,
    const MapSize& buildingSize
) :
    QGraphicsItem(parent),
    buildingGraphics(),
    forbiddenAreaGraphics(this),
    bounds(positioning.getBoundingRect(buildingSize))
{
    int areaPartIndex(0);
    for (auto areaPart : areaInformation) {
        auto& image(buildingImage.getAreaPartImage(orientation, areaPartIndex).getConstructionImage().getPixmap());
        auto areaPartGraphics(new QGraphicsPixmapItem(image, this));
        areaPartGraphics->setPos(
            positioning.getStaticElementPositionInTile(areaPart->size, image.height(), areaPart->position)
        );
        buildingGraphics.append(areaPartGraphics);
        ++areaPartIndex;
    }

    forbiddenAreaGraphics.setPolygon(positioning.getTileAreaPolygon(buildingSize));
    forbiddenAreaGraphics.setPen(Qt::NoPen);
    forbiddenAreaGraphics.setBrush(ImageLibrary::RED_BRUSH);

    setZValue(2.0);
}



ConstructionCursor::Cursor::~Cursor()
{
    qDeleteAll(buildingGraphics);
}



void ConstructionCursor::Cursor::updateStatus(bool isCoveredAreaFree)
{
    for (auto areaPartGraphics : buildingGraphics) {
        areaPartGraphics->setVisible(isCoveredAreaFree);
    }
    forbiddenAreaGraphics.setVisible(!isCoveredAreaFree);
}



QRectF ConstructionCursor::Cursor::boundingRect() const
{
    return bounds;
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
        this->path.append(coordinates);
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



const QList<MapCoordinates>& ConstructionCursor::RoadPath::getPath() const
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
    orientation(buildingConf.getAvailableOrientations().first()),
    coveredArea({0, 0}, buildingConf.getSize(orientation)),
    cursor(new Cursor(
        this,
        positioning,
        orientation,
        buildingConf.getAreaParts(orientation),
        buildingImage,
        buildingConf.getSize(orientation)
    )),
    roadPath(nullptr)
{
    setVisible(false);
}



ConstructionCursor::~ConstructionCursor()
{
    if (roadPath) {
        delete roadPath;
    }
    delete cursor;
}



void ConstructionCursor::displayAtLocation(const MapCoordinates& location)
{
    setVisible(true);
    cursor->setPos(positioning.getTilePosition(location));

    coveredArea.moveTo(location);
    refresh();
}



void ConstructionCursor::rotateBuilding()
{
    auto nextOrientation(resolveNextAvailableOrientation());
    if (nextOrientation == orientation) {
        return;
    }

    orientation = nextOrientation;

    // Replace cursor.
    delete cursor;
    cursor = new Cursor(
        this,
        positioning,
        orientation,
        buildingConf.getAreaParts(orientation),
        buildingImage,
        buildingConf.getSize(orientation)
    );
    cursor->setPos(positioning.getTilePosition(coveredArea.getLeft()));

    coveredArea = MapArea(coveredArea.getLeft(), buildingConf.getSize(orientation));
    refresh();
}



void ConstructionCursor::refresh()
{
    // TODO: Handle road construction for checking area: allow finishing on a Road.
    isCoveredAreaFree = areaChecker.isConstructible(coveredArea);
    cursor->updateStatus(isCoveredAreaFree);

    if (roadPath) {
        roadPath->refreshPath(roadPathGenerator.getShortestPathForRoad(roadPath->getOrigin(), coveredArea.getLeft()));
    }
}



QRectF ConstructionCursor::boundingRect() const
{
    // Translate cursor bouding rect to it's position.
    auto cursorBoundingRect(cursor->boundingRect());

    return {
        cursor->pos().x() + cursorBoundingRect.x(),
        cursor->pos().y() + cursorBoundingRect.y(),
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
        roadPath = new RoadPath(
            positioning,
            this,
            coveredArea.getLeft(),
            buildingImage.getAreaPartImage(orientation, 0).getInactiveImage().getPixmap()
        );
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
                            emit construct(buildingConf, roadPath->getPath(), orientation);
                            delete roadPath;
                            roadPath = nullptr;
                        }
                        break;

                    case SelectionType::Single:
                        emit construct(buildingConf, {coveredArea.getLeft()}, orientation);
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



Direction ConstructionCursor::resolveNextAvailableOrientation()
{
    auto availableOrientations(buildingConf.getAvailableOrientations());
    if (availableOrientations.length() == 1) {
        return availableOrientations.first();
    }

    // Find matching orientation in the list and return the next.
    bool previousOrientationMatched = false;
    for (auto availableOrientation : availableOrientations) {
        if (previousOrientationMatched) {
            return availableOrientation;
        }
        if (availableOrientation == orientation) {
            previousOrientationMatched = true;
        }
    }

    return availableOrientations.first();
}
