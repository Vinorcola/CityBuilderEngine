#include "BuildingAreaPartImage.hpp"

#include "src/viewer/image/ImageSequence.hpp"

ImageSequence BuildingAreaPartImage::EMPTY_ANIMATION({});



BuildingAreaPartImage::BuildingAreaPartImage(const BuildingAreaInformation::Graphics& graphicsConf, const QBrush& constructionBrush) :
    mainImage(graphicsConf.mainImagePath),
    constructionImage(mainImage, constructionBrush),
    animations()
{
    for (auto status : graphicsConf.animations.keys()) {
        animations.insert(status, new ImageSequence(graphicsConf.animations.value(status)));
    }
}



const Image& BuildingAreaPartImage::getConstructionImage() const
{
    return constructionImage;
}



const Image& BuildingAreaPartImage::getInactiveImage() const
{
    return mainImage;
}



const ImageSequence& BuildingAreaPartImage::getActiveAnimationSequence(BuildingStatus status) const
{
    if (!animations.contains(status)) {
        return EMPTY_ANIMATION;
    }

    return *animations.value(status);
}
