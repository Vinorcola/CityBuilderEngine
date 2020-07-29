#ifndef CHARACTERINFORMATION_HPP
#define CHARACTERINFORMATION_HPP

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtGui/QPixmap>

namespace YAML {
    class Node;
}

class CharacterInformation : public QObject
{
        Q_OBJECT

    public:
        enum class Type {
            None = 0,
            TargetedWalker,
            RandomWalker,
        };

    private:
        Type type;
        QString key;
        QString title;
        qreal speed;
        int wanderingCredits;
        QPixmap image;

    public:
        CharacterInformation(QObject* parent, const QString& key, const YAML::Node& model);

        bool operator ==(const CharacterInformation& other) const;

        Type getType() const;

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

    private:
        static Type resolveType(const QString& type);
};

#endif // CHARACTERINFORMATION_HPP
