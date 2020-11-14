#ifndef CHARACTERIMAGE_HPP
#define CHARACTERIMAGE_HPP

#include <QtCore/QHash>

#include "src/global/conf/CharacterInformation.hpp"
#include "src/global/Direction.hpp"
#include "src/viewer/image/Image.hpp"
#include "src/defines.hpp"

class ImageSequence;

/**
 * @brief Handles all the images required to display a character.
 */
class CharacterImage
{
        Q_DISABLE_COPY_MOVE(CharacterImage)

    private:
        QHash<Direction, owner<const ImageSequence*>> movingImageSequences;

    public:
        CharacterImage(const CharacterInformation::Graphics& graphicsData);

        ~CharacterImage();

        int getAnimationSequenceLength() const;

        const Image& getAnimationImage(int sequenceIndex, Direction direction) const;
};

#endif // CHARACTERIMAGE_HPP
