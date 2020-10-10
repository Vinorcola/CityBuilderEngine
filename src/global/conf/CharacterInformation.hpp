#ifndef CHARACTERINFORMATION_HPP
#define CHARACTERINFORMATION_HPP

#include <QtCore/QObject>
#include <QtCore/QString>

class ModelReader;
namespace YAML {
    class Node;
}

class CharacterInformation : public QObject
{
        Q_OBJECT

    private:
        QString key;
        QString title;
        qreal speed;
        int wanderingCredits;
        QString imagePath;

    public:
        CharacterInformation(QObject* parent, const ModelReader& model);

        const QString& getKey() const;

        const QString& getTitle() const;

        qreal getSpeed() const;

        int getWanderingCredits() const;

        const QString& getImagePath() const;

        /**
         * @brief Check if the model is valid.
         *
         * @throws BadConfigurationException Thrown if the model is invalid.
         */
        static void checkModel(const QString& key, const YAML::Node& model);
};

#endif // CHARACTERINFORMATION_HPP
