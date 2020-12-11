#ifndef BUILDINGAREAPARTIMAGE_HPP
#define BUILDINGAREAPARTIMAGE_HPP

#include "src/global/conf/BuildingAreaInformation.hpp"
#include "src/viewer/image/Image.hpp"
#include "src/defines.hpp"

class ImageSequence;

class BuildingAreaPartImage
{
        Q_DISABLE_COPY_MOVE(BuildingAreaPartImage)
        static ImageSequence EMPTY_ANIMATION;

    private:
        const Image mainImage;
        const Image constructionImage;
        QHash<BuildingStatus, owner<const ImageSequence*>> animations;

    public:
        BuildingAreaPartImage(const BuildingAreaInformation::Graphics& graphicsConf, const QBrush& constructionBrush);

        const Image& getConstructionImage() const;
        const Image& getInactiveImage() const;
        const ImageSequence& getActiveAnimationSequence(BuildingStatus status) const;
};

#endif // BUILDINGAREAPARTIMAGE_HPP
