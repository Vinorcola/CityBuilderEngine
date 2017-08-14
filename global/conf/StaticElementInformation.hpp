#ifndef STATICELEMENTINFORMATION_HPP
#define STATICELEMENTINFORMATION_HPP

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtGui/QPixmap>
#include <yaml-cpp/node/node.h>

#include "engine/map/searchEngine/StaticSearchCriteria.hpp"
#include "engine/map/MapSize.hpp"

class BehaviorInformation;
class Conf;
class DynamicElementInformation;
class StaticElementAreaPartDescription;
class StaticSearchCriteriaDescription;

class StaticElementInformation : public QObject
{
        Q_OBJECT

    public:
        enum class Type {
            None = 0,
            Building,
            CityEntryPoint,
            HousingBuilding,
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
        QList<BehaviorInformation*> behaviors;
        QPixmap image;

    public:
        /**
         * @brief Hold the information about a static element.
         *
         * @param configurationYamlNode The YAML node corresponding to a static element configuration.
         */
        StaticElementInformation(QObject* parent, const Conf* conf, const QString& key, const YAML::Node& model);

        void resolveDependencies(const Conf* conf);

        Type getType() const;

        const QString& getTitle() const;

        const MapSize& getSize() const;

        const QList<BehaviorInformation*>& getBehaviors() const;

        const QPixmap& getImage() const;

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

#endif // STATICELEMENTINFORMATION_HPP
