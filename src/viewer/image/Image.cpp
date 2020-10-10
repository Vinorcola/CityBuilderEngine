#include "Image.hpp"

#include <QtGui/QBitmap>
#include <QtGui/QPainter>

const QBrush Image::GREEN_BRUSH = QBrush(QColor(0, 224, 0, 127), Qt::SolidPattern);
const QBrush Image::ORANGE_BRUSH = QBrush(QColor(255, 154, 36, 127), Qt::SolidPattern);
const QBrush Image::RED_BRUSH = QBrush(QColor(244, 0, 0, 127), Qt::SolidPattern);



Image::Image(const QString& path) :
    sourceImage(path),
    mainImage(),
    imageMask(),
    greenColorizedImage(),
    orangeColorizedImage(),
    redColorizedImage()
{

}



const QPixmap& Image::getImage(Image::ColorFilter filter)
{
    switch (filter) {
        case ColorFilter::None:
            return getMainImage();

        case ColorFilter::Green:
            return getGreenColorizedImage();

        case ColorFilter::Orange:
            return getOrangeColorizedImage();

        case ColorFilter::Red:
            return getRedColorizedImage();
    }
}



const QPixmap& Image::getMainImage()
{
    if (mainImage.isNull()) {
        mainImage = QPixmap::fromImage(sourceImage);
    }

    return mainImage;
}



const QPixmap& Image::getGreenColorizedImage()
{
    if (greenColorizedImage.isNull()) {
        generateColoredImage(greenColorizedImage, Image::GREEN_BRUSH);
    }

    return greenColorizedImage;
}



const QPixmap& Image::getOrangeColorizedImage()
{
    if (orangeColorizedImage.isNull()) {
        generateColoredImage(orangeColorizedImage, Image::ORANGE_BRUSH);
    }

    return orangeColorizedImage;
}



const QPixmap& Image::getRedColorizedImage()
{
    if (redColorizedImage.isNull()) {
        generateColoredImage(redColorizedImage, Image::RED_BRUSH);
    }

    return redColorizedImage;
}



void Image::generateColoredImage(QPixmap& image, const QBrush& brush)
{
    image = getMainImage();
    QPainter painter(&image);
    painter.setClipRegion(getImageMask());
    painter.fillRect(image.rect(), brush);
    painter.end();
}



const QRegion& Image::getImageMask()
{
    if (imageMask.isNull()) {
        imageMask = QBitmap(QPixmap::fromImage(sourceImage.createAlphaMask()));
    }

    return imageMask;
}
