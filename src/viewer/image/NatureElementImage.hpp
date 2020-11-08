#ifndef NATUREELEMENTIMAGE_HPP
#define NATUREELEMENTIMAGE_HPP

#include <QtCore/QString>
#include <QtGui/QPixmap>

#include "src/viewer/image/Image.hpp"

class NatureElementImage
{
        Q_DISABLE_COPY_MOVE(NatureElementImage)

    private:
        const Image image;

    public:
        NatureElementImage(const QString& imagePath);

        const Image& getImage() const;
};

#endif // NATUREELEMENTIMAGE_HPP
