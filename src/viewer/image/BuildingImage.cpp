#include "BuildingImage.hpp"



BuildingImage::BuildingImage(
    const QString& buildingFolderPath,
    const QPoint& animationAnchorPoint,
    const QBrush& constructionBrush
) :
    mainImage(buildingFolderPath + "/main.png", {}),
    constructionImage(mainImage, constructionBrush),
    animationImageSequence(buildingFolderPath, animationAnchorPoint)
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



const ImageSequence& BuildingImage::getAnimationSequence() const
{
    return animationImageSequence;
}
