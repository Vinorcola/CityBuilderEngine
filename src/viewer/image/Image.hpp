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
 * An Image is loaded from a file path and provide a pixmap and a position.
 */
class Image
{
        Q_DISABLE_COPY_MOVE(Image)

    private:
        QPixmap pixmap;
        QPoint position;

    public:
        /**
         * @brief Load an image from a file.
         */
        Image(const QString& path, const QPoint& position);

        /**
         * @brief Create a colorized filter image using the source image as a shape pattern.
         */
        Image(const Image& source, const QBrush& brush);

        const QPixmap& getPixmap() const;

        const QPoint& getPosition() const;
};

#endif // COLORABLEIMAGE_HPP
