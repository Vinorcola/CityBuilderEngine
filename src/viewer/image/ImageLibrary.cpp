#include "ImageLibrary.hpp"

#include "src/exceptions/OutOfRangeException.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/NatureElementInformation.hpp"
#include "src/global/conf/Conf.hpp"
#include "src/viewer/image/BuildingImage.hpp"
#include "src/viewer/image/NatureElementImage.hpp"



ImageLibrary::ImageLibrary(const Conf& conf) :
    buildingImages(),
    natureElementImages()
{
    // Load building images.
    for (auto buildingKey : conf.getAllBuildingKeys()) {
        auto& buildingConf(conf.getBuildingConf(buildingKey));
        buildingImages.insert(&buildingConf, new BuildingImage(buildingConf.getImageFolderPath(), buildingConf.getAnimationAnchorPoint()));
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
    qDeleteAll(natureElementImages);
}



BuildingImage& ImageLibrary::getBuildingImage(const BuildingInformation& buildingConf) const
{
    if (!buildingImages.contains(&buildingConf)) {
        throw OutOfRangeException("No image in the library for building \"" + buildingConf.getTitle() + "\".");
    }

    return *buildingImages.value(&buildingConf);
}



NatureElementImage& ImageLibrary::getNatureElementImage(const NatureElementInformation& natureElementConf) const
{
    if (!natureElementImages.contains(&natureElementConf)) {
        throw OutOfRangeException("No image in the library for nature element \"" + natureElementConf.getTitle() + "\".");
    }

    return *natureElementImages.value(&natureElementConf);
}
