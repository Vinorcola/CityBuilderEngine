#ifndef STATICELEMENTINFORMATION_HPP
#define STATICELEMENTINFORMATION_HPP

#include <QList>
#include <QString>
#include <yaml-cpp/yaml.h>

#include "global/conf/StaticElementAreaPartDescription.hpp"

template<typename StaticElementInformation> using Onwer = StaticElementInformation;

class StaticElementInformation
{
    public:
        enum class Type
        {
            None = 0,
            Maintenance,
            Road,
        };

    private:
        Type type;
        QString key;
        int price;
        int requiredEmployees;
        int fireRiskIncrement;
        int damageRiskIncrement;
        QList<Owner<StaticElementAreaPartDescription*>> areaDescription;

    public:
        /**
         * @brief Hold the information about a static element.
         *
         * @param configurationYamlNode The YAML node corresponding to a static element configuration.
         */
        StaticElementInformation(const QString& key, YAML::Node model);

        Type getType() const;

    private:
        static Type resolveKeyToType(const QString& key);
};



// qHash function for using StaticElementInformation::Type as key.
inline uint qHash(StaticElementInformation::Type key, uint seed)
{
    return qHash(static_cast<uint>(key), seed);
}

#endif // STATICELEMENTINFORMATION_HPP
