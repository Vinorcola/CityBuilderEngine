#include "NatureElementImage.hpp"



NatureElementImage::NatureElementImage(const QString& imagePath) :
    image(imagePath, {})
{

}



const Image& NatureElementImage::getImage() const
{
    return image;
}
