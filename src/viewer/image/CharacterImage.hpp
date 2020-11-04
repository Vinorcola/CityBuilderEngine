#ifndef CHARACTERIMAGE_HPP
#define CHARACTERIMAGE_HPP

#include <QtCore/QHash>

#include "src/global/Direction.hpp"
#include "src/viewer/image/Image.hpp"

class CharacterInformation;
class ImageSequence;

class CharacterImage
{
        Q_DISABLE_COPY_MOVE(CharacterImage)

    private:
        QHash<Direction, const ImageSequence*> movingImageSequences;

    public:
        CharacterImage(const CharacterInformation& characterConf);

        ~CharacterImage();

        int getAnimationSequenceLength() const;

        const Image& getAnimationImage(int sequenceIndex, Direction direction) const;
};

#endif // CHARACTERIMAGE_HPP
