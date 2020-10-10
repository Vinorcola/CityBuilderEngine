#include "CharacterImage.hpp"



CharacterImage::CharacterImage(const QString& imagePath) :
    image(imagePath)
{

}



const QPixmap& CharacterImage::getImage()
{
    return image.getImage();
}
