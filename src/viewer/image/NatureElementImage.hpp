#ifndef NATUREELEMENTIMAGE_HPP
#define NATUREELEMENTIMAGE_HPP

#include <QtCore/QString>
#include <QtGui/QPixmap>

#include "src/viewer/image/Image.hpp"

class NatureElementImage
{
    private:
        Image image;

    public:
        NatureElementImage(const QString& imagePath);

        const QPixmap& getImage();
};

#endif // NATUREELEMENTIMAGE_HPP
