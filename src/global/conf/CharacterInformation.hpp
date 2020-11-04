#ifndef CHARACTERINFORMATION_HPP
#define CHARACTERINFORMATION_HPP

#include <QtCore/QHash>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QPoint>
#include <QtCore/QString>

#include "src/global/conf/ImageSequenceInformation.hpp"
#include "src/global/Direction.hpp"
#include "src/defines.hpp"

class ModelReader;
namespace YAML {
    class Node;
}

class CharacterInformation : public QObject
{
        Q_OBJECT

    private:
        struct Graphics {
            QHash<Direction, QList<const owner<ImageSequenceInformation>*>> walkingAnimation;

            ~Graphics();
        };

    private:
        QString key;
        QString title;
        qreal speed;
        int wanderingCredits;
        Graphics graphics;

    public:
        CharacterInformation(QObject* parent, const ModelReader& model);

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
