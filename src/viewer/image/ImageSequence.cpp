#include "ImageSequence.hpp"

#include <QtCore/QDir>



ImageSequence::ImageSequence(const QList<const ImageSequenceInformation*>& imagesSequenceInformations) :
    images()
{
    for (auto imageSequenceInformation : imagesSequenceInformations) {
        images.append(new Image(imageSequenceInformation->path, imageSequenceInformation->position));
    }
}


const QRegularExpression FILE_NAME_PATTERN("\\d\\d\\.png");
ImageSequence::ImageSequence(const QString& imagesFolderPath, const QPoint& imagesPosition)
{
    auto filePaths(QDir(imagesFolderPath).entryList());
    filePaths.sort();
    for (auto filePath : filePaths) {
        if (FILE_NAME_PATTERN.match(filePath).hasMatch()) {
            images.append(new Image(imagesFolderPath + "/" + filePath, imagesPosition));
        }
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
