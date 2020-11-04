#include "CharacterView.hpp"

#include "src/engine/element/dynamic/Character.hpp"
#include "src/viewer/element/graphics/DynamicElement.hpp"
#include "src/viewer/element/TileLocatorInterface.hpp"
#include "src/viewer/image/CharacterImage.hpp"
#include "src/viewer/image/ImageLibrary.hpp"
#include "src/viewer/Tile.hpp"



CharacterView::CharacterView(
    const TileLocatorInterface& tileLocator,
    const ImageLibrary& imageLibrary,
    const QSizeF& baseTileSize,
    const QSharedPointer<const Character>& engineData
) :
    tileLocator(tileLocator),
    baseTileSize(baseTileSize),
    engineData(engineData),
    currentTile(&tileLocator.getTileAt(engineData->getCurrentLocation())),
    image(imageLibrary.getCharacterImage(engineData->getConf())),
    graphicElement(new DynamicElement(
        baseTileSize,
        image.getAnimationImage(0, engineData->getCurrentDirection()),
        getPositionOnTile(engineData->getCurrentLocation())
    )),
    currentViewVersion(0), // TODO
    animationIndex(0)
{
    currentTile->registerDynamicElement(graphicElement);
}



CharacterView::~CharacterView()
{
    delete graphicElement;
}



void CharacterView::updateFromEngineData()
{
    auto engineData(this->engineData.toStrongRef());
    if (engineData.isNull()) {
        this->setDestroyed();
        return;
    }

    if (engineData->isViewUpToDate(currentViewVersion)) {
        return;
    }

    move(engineData->getCurrentLocation());
    advanceAnimation();
    graphicElement->setImage(image.getAnimationImage(animationIndex, engineData->getCurrentDirection()));
}



bool CharacterView::hasBeenDestroyed() const
{
    return engineData.isNull();
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

    graphicElement->updateLocation(getPositionOnTile(newLocation));
}



void CharacterView::advanceAnimation()
{
    animationIndex = (animationIndex + 1) % image.getAnimationSequenceLength();
}



void CharacterView::setDestroyed()
{
    engineData.clear();
    currentTile->unregisterDynamicElement(graphicElement);
}



QPointF CharacterView::getPositionOnTile(const MapCoordinates& globalLocation)
{
    qreal xDiff(globalLocation.getX() - currentTile->getCoordinates().getX());
    qreal yDiff(globalLocation.getY() - currentTile->getCoordinates().getY());

    return {
        xDiff * baseTileSize.width() / 2.0 + yDiff * baseTileSize.width() / 2.0,
        -xDiff * baseTileSize.height() / 2.0 + yDiff * baseTileSize.height() / 2.0
    };
}
