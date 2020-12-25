#ifndef CHARACTERINFORMATION_HPP
#define CHARACTERINFORMATION_HPP

#include <QtCore/QHash>
#include <QtCore/QList>
#include <QtCore/QString>

#include "src/global/Direction.hpp"
#include "src/defines.hpp"

class ImageSequenceInformation;
class ModelReader;
namespace YAML {
    class Node;
}

class CharacterInformation
{
        Q_DISABLE_COPY_MOVE(CharacterInformation)

    public:
        struct Graphics {
            QHash<Direction, QList<owner<const ImageSequenceInformation*>>> walkingAnimation;

            ~Graphics();
        };

    private:
        QString key;
        QString title;
        qreal speed;
        int wanderingCredits;
        int actionInterval;
        Graphics graphics;

    public:
        CharacterInformation(const QString& configDirectoryPath, const ModelReader& model);

        const QString& getKey() const;
        const QString& getTitle() const;
        qreal getSpeed() const;
        int getWanderingCredits() const;
        int getActionInterval() const;
        const Graphics& getGraphicsData() const;
};

#endif // CHARACTERINFORMATION_HPP
