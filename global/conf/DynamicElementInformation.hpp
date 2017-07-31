#ifndef DYNAMICELEMENTINFORMATION_HPP
#define DYNAMICELEMENTINFORMATION_HPP

#include <QObject>
#include <QPixmap>
#include <QString>
#include <yaml-cpp/yaml.h>

class DynamicElementInformation :public QObject
{
        Q_OBJECT

    public:
        enum class Type {
            None = 0,
            Immigrant,
            Superintendent,
        };

    private:
        Type type;
        QString key;
        qreal speed;
        int walkingCredit;
        QPixmap image;

    public:
        DynamicElementInformation(QObject* parent, const QString& key, YAML::Node model);

        Type getType() const;

        qreal getSpeed() const;

        int getWalkingCredit() const;

        const QPixmap& getImage() const;

    private:
        static Type resolveTypeFromKey(const QString& key);
};



// qHash function for using DynamicElementInformation::Type as key.
inline uint qHash(DynamicElementInformation::Type key, uint seed)
{
    return qHash(static_cast<uint>(key), seed);
}

#endif // DYNAMICELEMENTINFORMATION_HPP
