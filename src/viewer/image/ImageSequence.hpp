#ifndef IMAGESEQUENCE_HPP
#define IMAGESEQUENCE_HPP

#include <QtCore/QRegularExpression>
#include <QtCore/QString>
#include <QtCore/QList>

#include "src/global/conf/ImageSequenceInformation.hpp"
#include "src/viewer/image/Image.hpp"

/**
 * @brief A sequence of images that creates an animation.
 */
class ImageSequence
{
        Q_DISABLE_COPY_MOVE(ImageSequence)

    private:
        QList<const Image*> images;

    public:
        /**
         * @brief Load all the images of a sequence.
         */
        ImageSequence(const QList<const ImageSequenceInformation*>& imagesSequenceInformations);

        ~ImageSequence();

        int getSequenceLength() const;

        const Image& getImage(int sequenceIndex) const;
};

#endif // IMAGESEQUENCE_HPP
