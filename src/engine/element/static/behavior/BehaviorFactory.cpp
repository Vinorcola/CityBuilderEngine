#include "BehaviorFactory.hpp"

#include "src/engine/element/static/behavior/ConditionalRandomWalkerGenerator.hpp"
#include "src/engine/element/static/behavior/DeliverymanGenerator.hpp"
#include "src/engine/element/static/behavior/FarmBehavior.hpp"
#include "src/engine/element/static/behavior/InhabitantContainer.hpp"
#include "src/engine/element/static/behavior/ItemStorage.hpp"
#include "src/engine/element/static/behavior/QueuedWalkerGenerator.hpp"
#include "src/engine/element/static/behavior/RandomWalkerGenerator.hpp"
#include "src/engine/element/static/behavior/TargetedWalkerGenerator.hpp"
#include "src/engine/map/Map.hpp"
#include "src/exceptions/UnexpectedException.hpp"
#include "src/global/conf/BehaviorInformation.hpp"
#include "src/global/conf/CharacterInformation.hpp"



BehaviorFactory::BehaviorFactory(QObject* parent, const Map* map, const SearchEngine* searchEngine) :
    QObject(parent),
    map(map),
    searchEngine(searchEngine)
{

}



AbstractBehavior* BehaviorFactory::generate(ProcessableBuilding* issuer, const BehaviorInformation& conf) const
{
    switch (conf.getType()) {
        case BehaviorInformation::Type::ConditionalRandomWalkerGenerator: {
            auto behavior(new ConditionalRandomWalkerGenerator(
                issuer,
                *conf.getWalkerConf(),
                *conf.getDependencyWalkerConf(),
                conf.getWalkerGenerationInterval(),
                conf.getMaxWalkers()
            ));
            connect(behavior, &ConditionalRandomWalkerGenerator::requestDynamicElementCreation, map, &Map::createCharacter);
            connect(behavior, &ConditionalRandomWalkerGenerator::requestDynamicElementDestruction, map, &Map::destroyCharacter);

            return behavior;
        }

        case BehaviorInformation::Type::DeliverymanGenerator: {
            auto behavior(new DeliverymanGenerator(issuer, *conf.getWalkerConf()));

            return behavior;
        }

        case BehaviorInformation::Type::Farm: {
            auto behavior(new FarmBehavior(issuer, conf));

            return behavior;
        }

        case BehaviorInformation::Type::InhabitantContainer: {
            auto behavior(new InhabitantContainer(issuer));
            connect(behavior, &InhabitantContainer::requestDynamicElementDestruction, map, &Map::destroyCharacter);
            connect(behavior, &InhabitantContainer::freeCapacityChanged, map, &Map::freeHousingCapacityChanged);
            connect(behavior, &InhabitantContainer::inhabitantsChanged, map, &Map::changePopulation);

            return behavior;
        }

        case BehaviorInformation::Type::ItemStorage: {
            auto behavior(new ItemStorage(issuer, conf));

            return behavior;
        }

        case BehaviorInformation::Type::QueuedWalkerGenerator: {
            auto behavior(new QueuedWalkerGenerator(issuer, *conf.getWalkerConf(), conf.getMinWalkerGenerationInterval(), conf.getMaxWalkerGenerationInterval()));
            connect(behavior, &QueuedWalkerGenerator::requestDynamicElementCreation, map, &Map::createCharacter);

            return behavior;
        }

        case BehaviorInformation::Type::RandomWalkerGenerator:{
            auto behavior(new RandomWalkerGenerator(
                issuer,
                *conf.getWalkerConf(),
                conf.getWalkerGenerationInterval(),
                conf.getMaxWalkers()
            ));
            connect(behavior, &ConditionalRandomWalkerGenerator::requestDynamicElementCreation, map, &Map::createCharacter);
            connect(behavior, &ConditionalRandomWalkerGenerator::requestDynamicElementDestruction, map, &Map::destroyCharacter);

            return behavior;
        }

        case BehaviorInformation::Type::TargetedWalkerGenerator: {
            auto behavior(new TargetedWalkerGenerator(
                issuer,
                searchEngine,
                conf.getTargetSearchCriteria(),
                *conf.getWalkerConf(),
                conf.getWalkerGenerationInterval(),
                conf.getMaxWalkers()
            ));
            connect(behavior, &ConditionalRandomWalkerGenerator::requestDynamicElementCreation, map, &Map::createCharacter);
            connect(behavior, &ConditionalRandomWalkerGenerator::requestDynamicElementDestruction, map, &Map::destroyCharacter);

            return behavior;
        }

        default:
            throw UnexpectedException("Unknown behavior type.");
    }
}
