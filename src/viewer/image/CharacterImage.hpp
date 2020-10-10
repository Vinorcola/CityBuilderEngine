#ifndef CHARACTERIMAGE_HPP
#define CHARACTERIMAGE_HPP

#include <QtCore/QString>
#include <QtGui/QPixmap>

#include "src/viewer/image/Image.hpp"

class CharacterImage
{
    private:
        Image image;

    public:
        CharacterImage(const QString& imagePath);

        const QPixmap& getImage();
};

#endif // CHARACTERIMAGE_HPP
