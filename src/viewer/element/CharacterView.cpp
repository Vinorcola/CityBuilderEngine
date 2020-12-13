#include "CharacterView.hpp"

#include "src/global/state/CharacterState.hpp"
#include "src/viewer/element/graphics/DynamicElement.hpp"
#include "src/viewer/element/TileLocatorInterface.hpp"
#include "src/viewer/image/CharacterImage.hpp"
#include "src/viewer/image/ImageLibrary.hpp"
#include "src/viewer/Positioning.hpp"
#include "src/viewer/Tile.hpp"



CharacterView::CharacterView(
    const Positioning& positioning,
    const TileLocatorInterface& tileLocator,
    const ImageLibrary& imageLibrary,
    const CharacterState& state
) :
    positioning(positioning),
    tileLocator(tileLocator),
    currentTile(&tileLocator.getTileAt(state.position)),
    image(imageLibrary.getCharacterImage(state.type)),
    graphicElement(new DynamicElement(
        positioning,
        image.getAnimationImage(0, state.direction),
        state.position
    )),
    currentStateVersion(state.stateVersion),
    animationIndex(0)
{
    currentTile->registerDynamicElement(graphicElement);
}



CharacterView::~CharacterView()
{
    delete graphicElement;
}



void CharacterView::update(const CharacterState& state)
{
    if (state.stateVersion != currentStateVersion) {
        move(state.position);
        advanceAnimation();
        graphicElement->setImage(image.getAnimationImage(animationIndex, state.direction));

        currentStateVersion = state.stateVersion;
    }
}



void CharacterView::destroy()
{
    currentTile->unregisterDynamicElement(graphicElement);
}



void CharacterView::move(const MapCoordinates& newLocation)
{
    auto& previousTileLocation(currentTile->getCoordinates());
    auto newTileLocation(newLocation.getRounded());

    if (newTileLocation != previousTileLocation) {
        // Move character to another tile.
        auto& newTile(tileLocator.getTileAt(newTileLocation));
        currentTile->moveDynamicElementTo(graphicElement, newTile);
        currentTile = &newTile;
    }

    graphicElement->updateLocation(positioning.getDynamicElementPositionInTile(newLocation));
}



void CharacterView::advanceAnimation()
{
    animationIndex = (animationIndex + 1) % image.getAnimationSequenceLength();
}
