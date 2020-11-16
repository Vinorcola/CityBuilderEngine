#ifndef DYNAMICELEMENTHANDLER_HPP
#define DYNAMICELEMENTHANDLER_HPP

#include <list>

#include "src/engine/element/dynamic/CharacterFactoryInterface.hpp"
#include "src/engine/element/dynamic/CharacterManagerInterface.hpp"
#include "src/defines.hpp"

class BuildingSearchEngine;
class Character;
class PathGeneratorInterface;

class DynamicElementHandler : public CharacterFactoryInterface, public CharacterManagerInterface
{
    private:
        struct State {
            std::list<owner<Character*>> characters;
        };

    private:
        const PathGeneratorInterface& pathGenerator;
        const BuildingSearchEngine& buildingSearchEngine;
        State currentState;

    public:
        DynamicElementHandler(
            const PathGeneratorInterface& pathGenerator,
            const BuildingSearchEngine& buildingSearchEngine
        );
        virtual ~DynamicElementHandler();

        virtual DeliveryManCharacter& generateDeliveryMan(
            const CharacterInformation& conf,
            AbstractProcessableBuilding& issuer,
            const ItemInformation& transportedItemConf,
            const int transportedQuantity = 0
        ) override;
        virtual ImmigrantCharacter& generateImmigrant(
            const CharacterInformation& conf,
            AbstractProcessableBuilding& issuer,
            AbstractProcessableBuilding& target
        ) override;
        virtual MinerCharacter& generateMiner(
            const CharacterInformation& conf,
            AbstractProcessableBuilding& issuer,
            owner<PathInterface*> path
        ) override;
        virtual StudentCharacter& generateStudent(
            const CharacterInformation& conf,
            AbstractProcessableBuilding& issuer,
            AbstractProcessableBuilding& target
        ) override;
        virtual WanderingCharacter& generateWanderingCharacter(
            const CharacterInformation& conf,
            AbstractProcessableBuilding& issuer
        ) override;

        virtual void clearCharacter(Character& character) override;
};

#endif // DYNAMICELEMENTHANDLER_HPP
