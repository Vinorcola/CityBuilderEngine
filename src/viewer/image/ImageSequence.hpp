#ifndef IMAGESEQUENCE_HPP
#define IMAGESEQUENCE_HPP

#include <QtCore/QRegularExpression>
#include <QtCore/QString>
#include <QtCore/QList>

#include "src/viewer/image/Image.hpp"

/**
 * @brief A sequence of images that create an animation.
 */
class ImageSequence
{
        static const QRegularExpression FILE_NAME_PATTERN;

    private:
        QList<Image*> images;

    public:
        /**
         * @brief Load all the images of a sequence.
         *
         * The files must be named `XX.png` where X is a digit. Those images will be loaded in the alphabetical order
         * to build the sequence.
         */
        ImageSequence(const QString& imagesFolderPath);

        ~ImageSequence();

        int getSequenceLength() const;

        const QPixmap& getImage(int sequenceIndex, Image::ColorFilter filter = Image::ColorFilter::None);
};

#endif // IMAGESEQUENCE_HPP
