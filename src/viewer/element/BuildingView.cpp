#include "BuildingView.hpp"

#include "src/engine/element/static/Building.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/viewer/element/graphics/StaticElement.hpp"
#include "src/viewer/element/TileLocatorInterface.hpp"
#include "src/viewer/image/BuildingImage.hpp"
#include "src/viewer/image/ImageLibrary.hpp"
#include "src/viewer/Tile.hpp"



BuildingView::BuildingView(
    const Positioning& positioning,
    const TileLocatorInterface& tileLocator,
    const ImageLibrary& imageLibrary,
    const QSharedPointer<const Building>& engineData
) :
    tileLocator(tileLocator),
    engineData(engineData),
    buildingSize(engineData->getConf().getSize()),
    tile(tileLocator.getTileAt(engineData->getArea().getLeft())),
    image(imageLibrary.getBuildingImage(engineData->getConf())),
    graphicElement(new StaticElement(positioning, engineData->getConf().getSize(), image.getInactiveImage())),
    currentViewVersion(engineData->getViewVersion()),
    animationIndex(0)
{
    tile.setStaticElement(graphicElement);
    maskCoveredTiles();
}



BuildingView::~BuildingView()
{
    delete graphicElement;
}



void BuildingView::updateFromEngineData()
{
    auto engineData(this->engineData.toStrongRef());
    if (engineData.isNull()) {
        this->setDestroyed();
        return;
    }

    if (engineData->isViewUpToDate(currentViewVersion)) {
        return;
    }

    // TODO: Update data and change image if needed.
}



bool BuildingView::hasBeenDestroyed() const
{
    return engineData.isNull();
}



void BuildingView::advanceAnimation()
{
    auto& animation(image.getActiveAnimationSequence());
    if (animation.getSequenceLength() == 0) {
        return;
    }

    animationIndex = (animationIndex + 1) % animation.getSequenceLength();
    graphicElement->setAnimationImage(animation.getImage(animationIndex));
}



void BuildingView::maskCoveredTiles()
{
    if (buildingSize.getValue() > 1) {
        MapArea area(tile.getCoordinates(), buildingSize);
        auto left(area.getLeft());
        auto right(area.getRight());
        auto current(left.getEast());

        while (current.getY() <= right.getY()) {
            while (current.getX() <= right.getX()) {
                tileLocator.getTileAt(current).setVisible(false);
                current = current.getEast();
            }
            current.setX(left.getX());
            current = current.getSouth();
        }
    }
}



void BuildingView::revealCoveredTiles()
{
    if (buildingSize.getValue() > 1) {
        MapArea area(tile.getCoordinates(), buildingSize);
        auto left(area.getLeft());
        auto right(area.getRight());
        auto current(left.getEast());

        while (current.getY() <= right.getY()) {
            while (current.getX() <= right.getX()) {
                tileLocator.getTileAt(current).setVisible(true);
                current = current.getEast();
            }
            current.setX(left.getX());
            current = current.getSouth();
        }
    }
}



void BuildingView::setDestroyed()
{
    engineData.clear();
    tile.dropStaticElement();
    revealCoveredTiles();
}
