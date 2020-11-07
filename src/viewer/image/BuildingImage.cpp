#include "BuildingImage.hpp"

#include "src/viewer/image/ImageSequence.hpp"



BuildingImage::BuildingImage(const BuildingInformation::Graphics& graphicsData, const QBrush& constructionBrush) :
    mainImage(graphicsData.mainImagePath),
    constructionImage(mainImage, constructionBrush),
    animationImageSequence(graphicsData.activeAnimation)
{

}



const Image& BuildingImage::getConstructionImage() const
{
    return constructionImage;
}



const Image& BuildingImage::getInactiveImage() const
{
    return mainImage;
}



const ImageSequence& BuildingImage::getActiveAnimationSequence() const
{
    return animationImageSequence;
}
