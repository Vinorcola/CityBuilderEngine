#include "ImageLibrary.hpp"

#include "src/exceptions/OutOfRangeException.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/CharacterInformation.hpp"
#include "src/global/conf/Conf.hpp"
#include "src/global/conf/NatureElementInformation.hpp"
#include "src/viewer/image/BuildingImage.hpp"
#include "src/viewer/image/CharacterImage.hpp"
#include "src/viewer/image/NatureElementImage.hpp"

const QBrush ImageLibrary::GREEN_BRUSH = QBrush(QColor(0, 224, 0, 127), Qt::SolidPattern);
const QBrush ImageLibrary::ORANGE_BRUSH = QBrush(QColor(255, 154, 36, 127), Qt::SolidPattern);
const QBrush ImageLibrary::RED_BRUSH = QBrush(QColor(244, 0, 0, 127), Qt::SolidPattern);



ImageLibrary::ImageLibrary(const Conf& conf) :
    buildingImages(),
    characterImages(),
    natureElementImages()
{
    // Load building images.
    for (auto buildingKey : conf.getAllBuildingKeys()) {
        auto& buildingConf(conf.getBuildingConf(buildingKey));
        buildingImages.insert(&buildingConf, new BuildingImage(buildingConf, GREEN_BRUSH));
    }

    // Load character images.
    for (auto characterKey : conf.getAllCharacterKeys()) {
        auto& characterConf(conf.getCharacterConf(characterKey));
        characterImages.insert(&characterConf, new CharacterImage(characterConf.getGraphicsData()));
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



const BuildingImage& ImageLibrary::getBuildingImage(const BuildingInformation& buildingConf) const
{
    if (!buildingImages.contains(&buildingConf)) {
        throw OutOfRangeException("No image in the library for building \"" + buildingConf.getTitle() + "\".");
    }

    return *buildingImages.value(&buildingConf);
}



const CharacterImage& ImageLibrary::getCharacterImage(const CharacterInformation& characterConf) const
{
    if (!characterImages.contains(&characterConf)) {
        throw OutOfRangeException("No image in the library for character\"" + characterConf.getTitle() + "\".");
    }

    return *characterImages.value(&characterConf);
}



const NatureElementImage& ImageLibrary::getNatureElementImage(const NatureElementInformation& natureElementConf) const
{
    if (!natureElementImages.contains(&natureElementConf)) {
        throw OutOfRangeException("No image in the library for nature element \"" + natureElementConf.getTitle() + "\".");
    }

    return *natureElementImages.value(&natureElementConf);
}
