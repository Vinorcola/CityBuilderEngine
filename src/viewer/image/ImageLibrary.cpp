#include "ImageLibrary.hpp"

#include "src/exceptions/OutOfRangeException.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/CharacterInformation.hpp"
#include "src/global/conf/Conf.hpp"
#include "src/global/conf/NatureElementInformation.hpp"
#include "src/viewer/image/BuildingImage.hpp"
#include "src/viewer/image/CharacterImage.hpp"
#include "src/viewer/image/NatureElementImage.hpp"



ImageLibrary::ImageLibrary(const Conf& conf) :
    buildingImages(),
    characterImages(),
    natureElementImages()
{
    // Load building images.
    for (auto buildingKey : conf.getAllBuildingKeys()) {
        auto& buildingConf(conf.getBuildingConf(buildingKey));
        buildingImages.insert(&buildingConf, new BuildingImage(buildingConf.getImageFolderPath(), buildingConf.getAnimationAnchorPoint()));
    }

    // Load character images.
    for (auto characterKey : conf.getAllCharacterKeys()) {
        auto& characterConf(conf.getCharacterConf(characterKey));
        characterImages.insert(&characterConf, new CharacterImage(characterConf.getImagePath()));
    }

    // Load nature element images.
    for (auto natureElementKey : conf.getAllNatureElementKeys()) {
        auto& natureElementConf(conf.getNatureElementConf(natureElementKey));
        natureElementImages.insert(&natureElementConf, new NatureElementImage(natureElementConf.getImagePath()));
    }
}



ImageLibrary::~ImageLibrary()
{
    qDeleteAll(buildingImages);
    qDeleteAll(characterImages);
    qDeleteAll(natureElementImages);
}



BuildingImage& ImageLibrary::getBuildingImage(const BuildingInformation& buildingConf) const
{
    if (!buildingImages.contains(&buildingConf)) {
        throw OutOfRangeException("No image in the library for building \"" + buildingConf.getTitle() + "\".");
    }

    return *buildingImages.value(&buildingConf);
}



CharacterImage& ImageLibrary::getCharacterImage(const CharacterInformation& characterConf) const
{
    if (!characterImages.contains(&characterConf)) {
        throw OutOfRangeException("No image in the library for character\"" + characterConf.getTitle() + "\".");
    }

    return *characterImages.value(&characterConf);
}



NatureElementImage& ImageLibrary::getNatureElementImage(const NatureElementInformation& natureElementConf) const
{
    if (!natureElementImages.contains(&natureElementConf)) {
        throw OutOfRangeException("No image in the library for nature element \"" + natureElementConf.getTitle() + "\".");
    }

    return *natureElementImages.value(&natureElementConf);
}
