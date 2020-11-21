#include "BuildingView.hpp"

#include "src/engine/state/BuildingState.hpp"
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
    const BuildingState& state
) :
    tileLocator(tileLocator),
    buildingSize(state.type.getSize()),
    tile(tileLocator.getTileAt(state.area.getLeft())),
    image(imageLibrary.getBuildingImage(state.type)),
    graphicElement(new StaticElement(positioning, state.type.getSize(), image.getInactiveImage())),
    currentStateVersion(state.stateVersion),
    status(state.status),
    animationIndex(0)
{
    tile.setStaticElement(graphicElement);
    maskCoveredTiles();
}



BuildingView::~BuildingView()
{
    delete graphicElement;
}



void BuildingView::update(const BuildingState& state)
{
    if (state.stateVersion != currentStateVersion) {
        updateStatus(state.status);
        currentStateVersion = state.stateVersion;
    }
}



void BuildingView::destroy()
{
    tile.dropStaticElement();
    revealCoveredTiles();
}



void BuildingView::advanceAnimation()
{
    if (status != BuildingState::Status::Inactive) {
        auto& animation(image.getActiveAnimationSequence());
        if (animation.getSequenceLength() == 0) {
            return;
        }

        animationIndex = (animationIndex + 1) % animation.getSequenceLength();
        graphicElement->setAnimationImage(animation.getImage(animationIndex));
    }
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



void BuildingView::updateStatus(BuildingState::Status newStatus)
{
    if (newStatus != status) {
        if (newStatus == BuildingState::Status::Inactive) {
            graphicElement->dropAnimationImage();
            animationIndex = 0;
        }
        else {
            auto& animation(image.getActiveAnimationSequence());
            if (animation.getSequenceLength() > 0) {
                graphicElement->setAnimationImage(animation.getImage(animationIndex));
            }
        }

        status = newStatus;
    }
}
