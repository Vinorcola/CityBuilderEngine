#include "CharacterImage.hpp"

#include "src/viewer/image/ImageSequence.hpp"



CharacterImage::CharacterImage(const CharacterInformation::Graphics& graphicsData) :
    animations()
{
    for (auto status : graphicsData.animations.keys()) {
        auto& animationData(graphicsData.animations.value(status));
        CharacterStatusAnimation animation;
        animation.insert(Direction::Top, new ImageSequence(animationData.value(Direction::Top)));
        animation.insert(Direction::Right, new ImageSequence(animationData.value(Direction::Right)));
        animation.insert(Direction::Bottom, new ImageSequence(animationData.value(Direction::Bottom)));
        animation.insert(Direction::Left, new ImageSequence(animationData.value(Direction::Left)));
        animation.insert(Direction::North, new ImageSequence(animationData.value(Direction::North)));
        animation.insert(Direction::East, new ImageSequence(animationData.value(Direction::East)));
        animation.insert(Direction::South, new ImageSequence(animationData.value(Direction::South)));
        animation.insert(Direction::West, new ImageSequence(animationData.value(Direction::West)));
        animations.insert(status, animation);
    }
}



CharacterImage::~CharacterImage()
{
    for (auto statusAnimation : animations) {
        qDeleteAll(statusAnimation);
    }
}



int CharacterImage::getAnimationSequenceLength(CharacterStatus status) const
{
    if (!animations.contains(status)) {
        status = CharacterStatus::Walking;
    }

    return animations.value(status).value(Direction::Top)->getSequenceLength();
}



const Image& CharacterImage::getAnimationImage(CharacterStatus status, int sequenceIndex, Direction direction) const
{
    if (!animations.contains(status)) {
        status = CharacterStatus::Walking;
    }

    return animations.value(status).value(direction)->getImage(sequenceIndex);
}
