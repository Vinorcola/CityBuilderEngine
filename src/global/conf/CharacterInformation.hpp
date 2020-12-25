#ifndef CHARACTERINFORMATION_HPP
#define CHARACTERINFORMATION_HPP

#include <QtCore/QHash>
#include <QtCore/QList>
#include <QtCore/QString>

#include "src/global/CharacterStatus.hpp"
#include "src/global/Direction.hpp"
#include "src/defines.hpp"

class ImageSequenceInformation;
class ModelReader;
namespace YAML {
    class Node;
}

using OrientedAnimation = QHash<Direction, QList<owner<const ImageSequenceInformation*>>>;

class CharacterInformation
{
        Q_DISABLE_COPY_MOVE(CharacterInformation)

    public:
        struct Graphics {
            QHash<CharacterStatus, OrientedAnimation> animations;

            ~Graphics();
        };

        CharacterInformation(const QString& configDirectoryPath, const ModelReader& model);

        const QString& getKey() const;
        const QString& getTitle() const;
        qreal getSpeed() const;
        int getWanderingCredits() const;
        int getActionInterval() const;
        const Graphics& getGraphicsData() const;

    private:
        QString key;
        QString title;
        qreal speed;
        int wanderingCredits;
        int actionInterval;
        Graphics graphics;
};

#endif // CHARACTERINFORMATION_HPP
