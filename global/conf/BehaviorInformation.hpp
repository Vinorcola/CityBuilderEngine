#ifndef BEHAVIORINFORMATION_HPP
#define BEHAVIORINFORMATION_HPP

#include <QtCore/QObject>
#include <QtCore/QScopedPointer>

#include "engine/map/searchEngine/BuildingSearchCriteria.hpp"

class Conf;
class CharacterInformation;
class BuildingSearchCriteria;
class BuildingSearchCriteriaDescription;
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
            InhabitantContainer,
            QueuedWalkerGenerator,
            RandomWalkerGenerator,
            TargetedWalkerGenerator,
        };

    private:
        Type type;
        const CharacterInformation* dependencyWalkerConf;
        const CharacterInformation* walkerConf;
        const int walkerGenerationInterval;
        const int minWalkerGenerationInterval;
        const int maxWalkerGenerationInterval;
        const int maxWalkers;
        const BuildingSearchCriteriaDescription* targetSearchCriteriaDescription;
        QScopedPointer<BuildingSearchCriteria> targetSearchCriteria;

    public:
        BehaviorInformation(QObject* parent, const Conf* conf, const YAML::Node& model);

        void resolveDependencies(const Conf* conf);

        Type getType() const;

        const CharacterInformation* getDependencyWalkerConf() const;

        const CharacterInformation* getWalkerConf() const;

        int getWalkerGenerationInterval() const;

        int getMinWalkerGenerationInterval() const;

        int getMaxWalkerGenerationInterval() const;

        int getMaxWalkers() const;

        const BuildingSearchCriteria* getTargetSearchCriteria() const;

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
