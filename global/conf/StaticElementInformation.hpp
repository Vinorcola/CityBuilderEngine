#ifndef STATICELEMENTINFORMATION_HPP
#define STATICELEMENTINFORMATION_HPP

#include <QList>
#include <QPixmap>
#include <QString>
#include <yaml-cpp/yaml.h>

#include "global/conf/StaticElementAreaPartDescription.hpp"

class StaticElementInformation : public QObject
{
        Q_OBJECT

    public:
        enum class Type {
            None = 0,
            CityEntryPoint,
            House,
            Maintenance,
            Road,
        };

    private:
        Type type;
        QString key;
        MapSize size;
        int price;
        int employees;
        int fireRiskIncrement;
        int damageRiskIncrement;
        QList<StaticElementAreaPartDescription*> areaDescription;
        QPixmap image;

    public:
        /**
         * @brief Hold the information about a static element.
         *
         * @param configurationYamlNode The YAML node corresponding to a static element configuration.
         */
        StaticElementInformation(QObject* parent, const QString& key, YAML::Node model);

        Type getType() const;

        const MapSize& getSize() const;

        const QPixmap& getImage() const;

    private:
        static Type resolveTypeFromKey(const QString& key);
};



// qHash function for using StaticElementInformation::Type as key.
inline uint qHash(StaticElementInformation::Type key, uint seed)
{
    return qHash(static_cast<uint>(key), seed);
}

#endif // STATICELEMENTINFORMATION_HPP
