#include "BuildingView.hpp"

#include <cassert>

#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/state/BuildingState.hpp"
#include "src/viewer/element/graphics/StaticElement.hpp"
#include "src/viewer/element/TileLocatorInterface.hpp"
#include "src/viewer/image/BuildingAreaPartImage.hpp"
#include "src/viewer/image/BuildingImage.hpp"
#include "src/viewer/image/ImageLibrary.hpp"
#include "src/viewer/image/ImageSequence.hpp"
#include "src/viewer/TileView.hpp"



BuildingView::AreaPart::AreaPart(
    const Positioning& positioning,
    const TileLocatorInterface& tileLocator,
    const MapCoordinates& leftCorner,
    const MapSize& size,
    const BuildingAreaPartImage& image
) :
    tileLocator(tileLocator),
    size(size),
    tile(tileLocator.getTileAt(leftCorner)),
    image(image),
    graphicElement(positioning, size, image.getInactiveImage()),
    animationIndex(0)
{
    assert(size.isSquare());

    tile.setStaticElement(&graphicElement);
    maskCoveredTiles();
}



BuildingView::AreaPart::~AreaPart()
{
    tile.dropStaticElement();
    revealCoveredTiles();
}



void BuildingView::AreaPart::advanceAnimation(BuildingStatus status)
{
    auto& animation(image.getActiveAnimationSequence(status));
    if (animation.getSequenceLength() == 0) {
        return;
    }

    animationIndex = (animationIndex + 1) % animation.getSequenceLength();
    graphicElement.setAnimationImage(animation.getImage(animationIndex));
}



void BuildingView::AreaPart::updateStatus(BuildingStatus status)
{
    graphicElement.dropAnimationImage();
    animationIndex = 0;

    if (status != BuildingStatus::Inactive) {
        auto& animation(image.getActiveAnimationSequence(status));
        if (animation.getSequenceLength() > 0) {
            graphicElement.setAnimationImage(animation.getImage(animationIndex));
        }
    }
}



void BuildingView::AreaPart::maskCoveredTiles()
{
    if (size.getWidth() > 1) {
        MapArea area(tile.getCoordinates(), size);
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



void BuildingView::AreaPart::revealCoveredTiles()
{
    if (size.getWidth() > 1) {
        MapArea area(tile.getCoordinates(), size);
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



BuildingView::BuildingView(
    const Positioning& positioning,
    const TileLocatorInterface& tileLocator,
    const ImageLibrary& imageLibrary,
    const BuildingState& state
) :
    areaParts(),
    currentState(state)
{
    auto& buildingImage(imageLibrary.getBuildingImage(state.type));
    int areaPartIndex(0);
    for (auto areaPartConf : state.type.getAreaParts(state.orientation)) {
        areaParts.append(new AreaPart(
            positioning,
            tileLocator,
            { state.area.getLeft(), areaPartConf->position },
            areaPartConf->size,
            buildingImage.getAreaPartImage(state.orientation, areaPartIndex)
        ));
        ++areaPartIndex;
    }
}



const BuildingState& BuildingView::getCurrentState() const
{
    return currentState;
}



void BuildingView::update(const BuildingState& state)
{
    if (state.stateVersion != currentState.stateVersion) {
        if (state.status != currentState.status) {
            for (auto areaPart : areaParts) {
                areaPart->updateStatus(state.status);
            }
        }
        currentState = state;
    }
}



void BuildingView::destroy()
{
    qDeleteAll(areaParts);
    areaParts.clear();
}



void BuildingView::advanceAnimation()
{
    if (currentState.status != BuildingStatus::Inactive) {
        for (auto areaPart : areaParts) {
            areaPart->advanceAnimation(currentState.status);
        }
    }
}
