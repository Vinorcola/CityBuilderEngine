#ifndef BUILDINGIMAGE_HPP
#define BUILDINGIMAGE_HPP

#include <QtCore/QPoint>
#include <QtCore/QString>
#include <QtGui/QPixmap>

#include "src/viewer/image/Image.hpp"
#include "src/viewer/image/ImageSequence.hpp"

/**
 * @brief A handler for a building images.
 *
 * It will load and handle all the images needed to display a building.
 */
class BuildingImage
{
    private:
        Image mainImage;
        QPoint animationAnchorPoint;
        ImageSequence animationImageSequence;

    public:
        /**
         * @brief Load all the image from a folder.
         *
         * Note that the folder must contains at least one image named `main.png`. Optionally, it can contains
         * additional images named `XX.png` where X is a digit. Those images will be loaded in the alphabetical order
         * to build the animation.
         */
        BuildingImage(const QString& buildingFolderPath, const QPoint& animationAnchorPoint);

        const QPixmap& getConstructionImage();

        const QPixmap& getInactiveImage();

        const QPoint& getAnimationAnchorPoint() const;

        ImageSequence& getAnimationSequence();
};

#endif // BUILDINGIMAGE_HPP
