#ifndef STATICELEMENTINFORMATION_HPP
#define STATICELEMENTINFORMATION_HPP

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtGui/QPixmap>
#include <yaml-cpp/node/node.h>

#include "global/conf/StaticElementAreaPartDescription.hpp"

class Conf;
class DynamicElementInformation;

class StaticElementInformation : public QObject
{
        Q_OBJECT

    public:
        enum class Type {
            None = 0,
            CityEntryPoint,
            CultureBuilding,
            HousingBuilding,
            ServiceBuilding,
            Road,
        };

    private:
        Type type;
        QString key;
        QString title;
        MapSize size;
        int price;
        int employees;
        int fireRiskIncrement;
        int damageRiskIncrement;
        QList<StaticElementAreaPartDescription*> areaDescription;
        QPixmap image;
        const DynamicElementInformation* randomWalkerConf;
        int randomWalkerInterval;
        int maxNumberOfRandomWalkers;
        const DynamicElementInformation* targetedWalkerConf;
        int targetedWalkerInterval;

    public:
        /**
         * @brief Hold the information about a static element.
         *
         * @param configurationYamlNode The YAML node corresponding to a static element configuration.
         */
        StaticElementInformation(QObject* parent, const Conf* conf, const QString& key, const YAML::Node& model);

        Type getType() const;

        const QString& getTitle() const;

        const MapSize& getSize() const;

        const QPixmap& getImage() const;

        const DynamicElementInformation* getRandomWalkerConf() const;

        int getRandomWalkerGenerationInterval() const;

        int getMaxNumberOfRandomWalkers() const;

        const DynamicElementInformation* getTargetedWalkerConf() const;

        int getTargetedWalkerGenerationInterval() const;

        /**
         * @brief Check if the model for a static element is valid.
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



// qHash function for using StaticElementInformation::Type as key.
inline uint qHash(StaticElementInformation::Type key, uint seed)
{
    return qHash(static_cast<uint>(key), seed);
}

#endif // STATICELEMENTINFORMATION_HPP
