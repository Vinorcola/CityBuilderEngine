#ifndef DYNAMICELEMENTINFORMATION_HPP
#define DYNAMICELEMENTINFORMATION_HPP

#include <QObject>
#include <QPixmap>
#include <QString>
#include <yaml-cpp/yaml.h>

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
        DynamicElementInformation(QObject* parent, const QString& key, YAML::Node model);

        Type getType() const;

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



// qHash function for using DynamicElementInformation::Type as key.
inline uint qHash(DynamicElementInformation::Type key, uint seed)
{
    return qHash(static_cast<uint>(key), seed);
}

#endif // DYNAMICELEMENTINFORMATION_HPP
