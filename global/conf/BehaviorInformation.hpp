#ifndef BEHAVIORINFORMATION_HPP
#define BEHAVIORINFORMATION_HPP

#include <QtCore/QObject>
#include <QtCore/QScopedPointer>

#include "engine/map/searchEngine/StaticSearchCriteria.hpp"

class Conf;
class DynamicElementInformation;
class StaticSearchCriteria;
class StaticSearchCriteriaDescription;
namespace YAML {
    class Node;
}

class BehaviorInformation : public QObject
{
        Q_OBJECT

    public:
        enum class Type {
            None = 0,
            ConditionalRandomWalkerGenerator,
            RandomWalkerGenerator,
            TargetedWalkerGenerator,
        };

    private:
        Type type;
        const DynamicElementInformation* dependencyWalkerConf;
        const DynamicElementInformation* walkerConf;
        const int walkerGenerationInterval;
        const int maxWalkers;
        const StaticSearchCriteriaDescription* targetSearchCriteriaDescription;
        QScopedPointer<StaticSearchCriteria> targetSearchCriteria;

    public:
        BehaviorInformation(QObject* parent, const Conf* conf, const YAML::Node& model);

        void resolveDependencies(const Conf* conf);

        Type getType() const;

        const DynamicElementInformation* getDependencyWalkerConf() const;

        const DynamicElementInformation* getWalkerConf() const;

        int getWalkerGenerationInterval() const;

        int getMaxWalkers() const;

        const StaticSearchCriteria* getTargetSearchCriteria() const;

        /**
         * @brief Check if the model for a behavior is valid.
         *
         * If the model is invalid, it throws an exception.
         *
         * @param key   The static element's key.
         * @param model
         * @throws BadConfigurationException
         */
        static void checkModel(const QString& key, const YAML::Node& model);

    private:
        static Type resolveType(const QString& type);
};

#endif // BEHAVIORINFORMATION_HPP
