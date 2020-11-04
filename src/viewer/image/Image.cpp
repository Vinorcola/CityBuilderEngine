#include "Image.hpp"

#include <QtGui/QBitmap>
#include <QtGui/QPainter>

#include "src/exceptions/FileNotFoundException.hpp"



Image::Image(const QString& path, const QPoint& position) :
    pixmap(path),
    position(position)
{
    if (pixmap.isNull()) {
        throw FileNotFoundException(path);
    }
}



Image::Image(const Image& source, const QBrush& brush) :
    pixmap(source.pixmap.size()),
    position(source.position)
{
    QRegion mask(QBitmap(QPixmap::fromImage(pixmap.toImage().createAlphaMask())));
    QPainter painter(&pixmap);
    painter.setClipRegion(mask);
    painter.fillRect(pixmap.rect(), brush);
    painter.end();
}



const QPixmap& Image::getPixmap() const
{
    return pixmap;
}



const QPoint& Image::getPosition() const
{
    return position;
}
