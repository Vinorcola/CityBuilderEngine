#include "ImageSequence.hpp"

#include <cassert>
#include <QtCore/QDir>

const QRegularExpression ImageSequence::FILE_NAME_PATTERN("\\d\\d\\.png");



ImageSequence::ImageSequence(const QString& imagesFolderPath) :
    images()
{
    auto filePaths(QDir(imagesFolderPath).entryList());
    filePaths.sort();
    for (auto filePath : filePaths) {
        if (ImageSequence::FILE_NAME_PATTERN.match(filePath).hasMatch()) {
            images.append(new Image(filePath));
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



const QPixmap& ImageSequence::getImage(int sequenceIndex, Image::ColorFilter filter)
{
    assert(sequenceIndex < images.length());
    auto image(images.at(sequenceIndex));

    return image->getImage(filter);
}
