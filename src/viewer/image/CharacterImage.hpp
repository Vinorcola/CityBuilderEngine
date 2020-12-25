#ifndef CHARACTERIMAGE_HPP
#define CHARACTERIMAGE_HPP

#include <QtCore/QHash>

#include "src/global/conf/CharacterInformation.hpp"
#include "src/global/Direction.hpp"
#include "src/viewer/image/Image.hpp"
#include "src/defines.hpp"

class ImageSequence;

using CharacterStatusAnimation = QHash<Direction, owner<const ImageSequence*>>;

/**
 * @brief Handles all the images required to display a character.
 */
class CharacterImage
{
        Q_DISABLE_COPY_MOVE(CharacterImage)

    public:
        CharacterImage(const CharacterInformation::Graphics& graphicsData);
        ~CharacterImage();

        int getAnimationSequenceLength(CharacterStatus status) const;
        const Image& getAnimationImage(CharacterStatus status, int sequenceIndex, Direction direction) const;

    private:
        QHash<CharacterStatus, CharacterStatusAnimation> animations;
};

#endif // CHARACTERIMAGE_HPP
