#ifndef CHARACTERINFORMATION_HPP
#define CHARACTERINFORMATION_HPP

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtGui/QPixmap>

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
        QPixmap image;

    public:
        CharacterInformation(QObject* parent, const ModelReader& model);

        const QString& getKey() const;

        const QString& getTitle() const;

        qreal getSpeed() const;

        int getWanderingCredits() const;

        const QPixmap& getImage() const;

        /**
         * @brief Check if the model is valid.
         *
         * @throws BadConfigurationException Thrown if the model is invalid.
         */
        static void checkModel(const QString& key, const YAML::Node& model);
};

#endif // CHARACTERINFORMATION_HPP
