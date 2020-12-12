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
        Graphics graphics;

    public:
        CharacterInformation(const QString& configDirectoryPath, const ModelReader& model);

        const QString& getKey() const;

        const QString& getTitle() const;

        qreal getSpeed() const;

        int getWanderingCredits() const;

        const Graphics& getGraphicsData() const;

        /**
         * @brief Check if the model is valid.
         *
         * @throws BadConfigurationException Thrown if the model is invalid.
         */
        static void checkModel(const QString& key, const YAML::Node& model);
};

#endif // CHARACTERINFORMATION_HPP
