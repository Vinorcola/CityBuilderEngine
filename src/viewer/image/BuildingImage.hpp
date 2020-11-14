#ifndef BUILDINGIMAGE_HPP
#define BUILDINGIMAGE_HPP

#include "src/global/conf/BuildingInformation.hpp"
#include "src/viewer/image/Image.hpp"
#include "src/viewer/image/ImageSequence.hpp"
#include "src/defines.hpp"

/**
 * @brief Handles all the images required to display a building.
 */
class BuildingImage
{
        Q_DISABLE_COPY_MOVE(BuildingImage)

    private:
        const Image mainImage;
        const Image constructionImage;
        const ImageSequence animationImageSequence;

    public:
        BuildingImage(const BuildingInformation::Graphics& graphicsData, const QBrush& constructionBrush);

        const Image& getConstructionImage() const;

        const Image& getInactiveImage() const;

        const ImageSequence& getActiveAnimationSequence() const;
};

#endif // BUILDINGIMAGE_HPP
