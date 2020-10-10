#ifndef COLORABLEIMAGE_HPP
#define COLORABLEIMAGE_HPP

#include <QtCore/QString>
#include <QtGui/QBrush>
#include <QtGui/QImage>
#include <QtGui/QPixmap>
#include <QtGui/QRegion>

/**
 * @brief A low-level class that handle an image.
 *
 * An Image is loaded from a file path and can be get via the `getImage` method. Optionally, a colorized filter can be
 * applied on it. The available colors are green, orange or red.
 */
class Image
{
        Q_DISABLE_COPY_MOVE(Image)

        static const QBrush GREEN_BRUSH;
        static const QBrush ORANGE_BRUSH;
        static const QBrush RED_BRUSH;

    public:
        enum class ColorFilter {
            None,
            Green,
            Orange,
            Red,
        };

    private:
        QImage sourceImage;
        QPixmap mainImage;
        QRegion imageMask;
        QPixmap greenColorizedImage;
        QPixmap orangeColorizedImage;
        QPixmap redColorizedImage;

    public:
        explicit Image(const QString& path);

        const QPixmap& getImage(ColorFilter filter = ColorFilter::None);

    private:
        const QPixmap& getMainImage();

        const QPixmap& getGreenColorizedImage();

        const QPixmap& getOrangeColorizedImage();

        const QPixmap& getRedColorizedImage();

        void generateColoredImage(QPixmap& image, const QBrush& brush);

        const QRegion& getImageMask();
};

#endif // COLORABLEIMAGE_HPP
