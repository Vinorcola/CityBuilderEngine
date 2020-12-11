#include "BuildingAreaPartImage.hpp"



BuildingAreaPartImage::BuildingAreaPartImage(const BuildingAreaInformation::Graphics& graphicsConf, const QBrush& constructionBrush) :
    mainImage(graphicsConf.mainImagePath),
    constructionImage(mainImage, constructionBrush),
    animationImageSequence(graphicsConf.activeAnimation)
{

}



const Image& BuildingAreaPartImage::getConstructionImage() const
{
    return constructionImage;
}



const Image& BuildingAreaPartImage::getInactiveImage() const
{
    return mainImage;
}



const ImageSequence& BuildingAreaPartImage::getActiveAnimationSequence() const
{
    return animationImageSequence;
}
