#ifndef DYNAMICELEMENTINFORMATION_HPP
#define DYNAMICELEMENTINFORMATION_HPP

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtGui/QPixmap>

namespace YAML {
    class Node;
}

class DynamicElementInformation : public QObject
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
        int walkingCredit;
        QPixmap image;

    public:
        DynamicElementInformation(QObject* parent, const QString& key, const YAML::Node& model);

        Type getType() const;

        const QString& getKey() const;

        const QString& getTitle() const;

        qreal getSpeed() const;

        int getWalkingCredit() const;

        const QPixmap& getImage() const;

        /**
         * @brief Check if the model for a dynamic element is valid.
         *
         * If the model is invalid, it throws an exception.
         *
         * @param key
         * @param model
         * @throws BadConfigurationException
         */
        static void checkModel(const QString& key, const YAML::Node& model);

    private:
        static Type resolveType(const QString& type);
};

#endif // DYNAMICELEMENTINFORMATION_HPP
