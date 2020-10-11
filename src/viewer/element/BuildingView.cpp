#include "BuildingView.hpp"

#include "src/engine/element/static/Building.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/viewer/element/graphics/StaticElement.hpp"
#include "src/viewer/image/BuildingImage.hpp"
#include "src/viewer/image/ImageLibrary.hpp"
#include "src/viewer/Tile.hpp"



BuildingView::BuildingView(
    ImageLibrary& imageLibrary,
    const QSize& baseTileSize,
    const QSharedPointer<const Building>& engineData,
    Tile& tile
) :
    baseTileSize(baseTileSize),
    engineData(engineData),
    tile(tile),
    image(imageLibrary.getBuildingImage(engineData->getConf())),
    graphicElement(new StaticElement(baseTileSize, engineData->getConf().getSize(), image.getInactiveImage())),
    currentViewVersion(engineData->getViewVersion()),
    animationIndex(0)
{
    tile.setStaticElement(graphicElement);
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



void BuildingView::setDestroyed()
{
    this->engineData.clear();
    tile.dropStaticElement();
}
