#include "NatureElementImage.hpp"



NatureElementImage::NatureElementImage(const QString& imagePath) :
    image(imagePath)
{

}



const QPixmap& NatureElementImage::getImage()
{
    return image.getImage();
}
