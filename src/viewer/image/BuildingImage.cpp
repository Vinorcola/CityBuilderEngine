#include "BuildingImage.hpp"



BuildingImage::BuildingImage(const QString& buildingFolderPath, const QPoint& animationAnchorPoint) :
    mainImage(buildingFolderPath + "/main.png"),
    animationAnchorPoint(animationAnchorPoint),
    animationImageSequence(buildingFolderPath)
{

}



const QPixmap& BuildingImage::getConstructionImage()
{
    return mainImage.getImage(Image::ColorFilter::Green);
}



const QPixmap& BuildingImage::getInactiveImage()
{
    return mainImage.getImage();
}



const QPoint& BuildingImage::getAnimationAnchorPoint() const
{
    return animationAnchorPoint;
}



ImageSequence& BuildingImage::getAnimationSequence()
{
    return animationImageSequence;
}
