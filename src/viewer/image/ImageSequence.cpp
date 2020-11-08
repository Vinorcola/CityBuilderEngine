#include "ImageSequence.hpp"

#include <QtCore/QDir>



ImageSequence::ImageSequence(const QList<const ImageSequenceInformation*>& imagesSequenceInformations) :
    images()
{
    for (auto imageSequenceInformation : imagesSequenceInformations) {
        images.append(new Image(imageSequenceInformation->path, imageSequenceInformation->position));
    }
}



ImageSequence::~ImageSequence()
{
    qDeleteAll(images);
}



int ImageSequence::getSequenceLength() const
{
    return images.length();
}



const Image& ImageSequence::getImage(int sequenceIndex) const
{
    return *images.at(sequenceIndex % images.length());
}
