#ifndef BUILDINGAREAPARTIMAGE_HPP
#define BUILDINGAREAPARTIMAGE_HPP

#include "src/global/conf/BuildingAreaInformation.hpp"
#include "src/viewer/image/Image.hpp"
#include "src/viewer/image/ImageSequence.hpp"
#include "src/defines.hpp"

class BuildingAreaPartImage
{
        Q_DISABLE_COPY_MOVE(BuildingAreaPartImage)

    private:
        const Image mainImage;
        const Image constructionImage;
        const ImageSequence animationImageSequence;

    public:
        BuildingAreaPartImage(const BuildingAreaInformation::Graphics& graphicsConf, const QBrush& constructionBrush);

        const Image& getConstructionImage() const;
        const Image& getInactiveImage() const;
        const ImageSequence& getActiveAnimationSequence() const;
};

#endif // BUILDINGAREAPARTIMAGE_HPP
