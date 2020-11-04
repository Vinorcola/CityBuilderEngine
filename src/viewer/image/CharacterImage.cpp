#include "CharacterImage.hpp"

#include "src/global/conf/CharacterInformation.hpp"
#include "src/viewer/image/ImageSequence.hpp"



CharacterImage::CharacterImage(const CharacterInformation& characterConf) :
    movingImageSequences()
{
    auto& graphicsData(characterConf.getGraphicsData());
    movingImageSequences.insert(Direction::Top, new ImageSequence(graphicsData.walkingAnimation.value(Direction::Top)));
    movingImageSequences.insert(Direction::Right, new ImageSequence(graphicsData.walkingAnimation.value(Direction::Right)));
    movingImageSequences.insert(Direction::Bottom, new ImageSequence(graphicsData.walkingAnimation.value(Direction::Bottom)));
    movingImageSequences.insert(Direction::Left, new ImageSequence(graphicsData.walkingAnimation.value(Direction::Left)));
    movingImageSequences.insert(Direction::North, new ImageSequence(graphicsData.walkingAnimation.value(Direction::North)));
    movingImageSequences.insert(Direction::East, new ImageSequence(graphicsData.walkingAnimation.value(Direction::East)));
    movingImageSequences.insert(Direction::South, new ImageSequence(graphicsData.walkingAnimation.value(Direction::South)));
    movingImageSequences.insert(Direction::West, new ImageSequence(graphicsData.walkingAnimation.value(Direction::West)));
}



CharacterImage::~CharacterImage()
{
    qDeleteAll(movingImageSequences);
}



int CharacterImage::getAnimationSequenceLength() const
{
    return movingImageSequences.value(Direction::Top)->getSequenceLength();
}



const Image& CharacterImage::getAnimationImage(int sequenceIndex, Direction direction) const
{
    return movingImageSequences.value(direction)->getImage(sequenceIndex);
}
