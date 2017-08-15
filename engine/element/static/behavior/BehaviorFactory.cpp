#include "BehaviorFactory.hpp"

#include "engine/element/static/behavior/ConditionalRandomWalkerGenerator.hpp"
#include "engine/element/static/behavior/InhabitantContainer.hpp"
#include "engine/element/static/behavior/QueuedWalkerGenerator.hpp"
#include "engine/element/static/behavior/RandomWalkerGenerator.hpp"
#include "engine/element/static/behavior/TargetedWalkerGenerator.hpp"
#include "engine/map/Map.hpp"
#include "exceptions/UnexpectedException.hpp"
#include "global/conf/BehaviorInformation.hpp"
#include "global/conf/DynamicElementInformation.hpp"



BehaviorFactory::BehaviorFactory(QObject* parent, const Map* map, const SearchEngine* searchEngine) :
    QObject(parent),
    map(map),
    searchEngine(searchEngine)
{

}



AbstractStaticElementBehavior* BehaviorFactory::generate(
    AbstractProcessableStaticMapElement* issuer,
    const BehaviorInformation* conf
) const
{
    switch (conf->getType()) {
        case BehaviorInformation::Type::ConditionalRandomWalkerGenerator: {
            auto behavior(new ConditionalRandomWalkerGenerator(
                issuer,
                conf->getWalkerConf(),
                conf->getDependencyWalkerConf(),
                conf->getWalkerGenerationInterval(),
                conf->getMaxWalkers()
            ));
            connect(behavior, &ConditionalRandomWalkerGenerator::requestDynamicElementCreation, map, &Map::createDynamicElement);
            connect(behavior, &ConditionalRandomWalkerGenerator::requestDynamicElementDestruction, map, &Map::destroyElement);

            return behavior;
        }

        case BehaviorInformation::Type::InhabitantContainer: {
            auto behavior(new InhabitantContainer(issuer));
            connect(behavior, &InhabitantContainer::requestDynamicElementDestruction, map, &Map::destroyElement);
            connect(behavior, &InhabitantContainer::freeCapacityChanged, map, &Map::freeHousingCapacityChanged);
            connect(behavior, &InhabitantContainer::inhabitantsChanged, map, &Map::populationChanged);

            return behavior;
        }

        case BehaviorInformation::Type::QueuedWalkerGenerator: {
            auto behavior(new QueuedWalkerGenerator(issuer, conf->getWalkerConf(), conf->getMinWalkerGenerationInterval(), conf->getMaxWalkerGenerationInterval()));
            connect(behavior, &QueuedWalkerGenerator::requestDynamicElementCreation, map, &Map::createDynamicElement);

            return behavior;
        }

        case BehaviorInformation::Type::RandomWalkerGenerator:{
            auto behavior(new RandomWalkerGenerator(
                issuer,
                conf->getWalkerConf(),
                conf->getWalkerGenerationInterval(),
                conf->getMaxWalkers()
            ));
            connect(behavior, &ConditionalRandomWalkerGenerator::requestDynamicElementCreation, map, &Map::createDynamicElement);
            connect(behavior, &ConditionalRandomWalkerGenerator::requestDynamicElementDestruction, map, &Map::destroyElement);

            return behavior;
        }

        case BehaviorInformation::Type::TargetedWalkerGenerator: {
            auto behavior(new TargetedWalkerGenerator(
                issuer,
                searchEngine,
                conf->getTargetSearchCriteria(),
                conf->getWalkerConf(),
                conf->getWalkerGenerationInterval(),
                conf->getMaxWalkers()
            ));
            connect(behavior, &ConditionalRandomWalkerGenerator::requestDynamicElementCreation, map, &Map::createDynamicElement);
            connect(behavior, &ConditionalRandomWalkerGenerator::requestDynamicElementDestruction, map, &Map::destroyElement);

            return behavior;
        }

        default:
            throw UnexpectedException("Unknown behavior type.");
    }
}
