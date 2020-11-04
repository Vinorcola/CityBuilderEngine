#ifndef IMAGESEQUENCEINFORMATION_HPP
#define IMAGESEQUENCEINFORMATION_HPP

#include <QtCore/QPoint>
#include <QtCore/QString>

struct ImageSequenceInformation
{
    Q_DISABLE_COPY_MOVE(ImageSequenceInformation)

    QString path;
    QPoint position;

    ImageSequenceInformation(const QString& path, const QPoint& position);
};

#endif // IMAGESEQUENCEINFORMATION_HPP
