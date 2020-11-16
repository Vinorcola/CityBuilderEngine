#ifndef DELIVERYMANCHARACTER_HPP
#define DELIVERYMANCHARACTER_HPP

#include "src/engine/element/dynamic/character/Character.hpp"

class AbstractProcessableBuilding;
class BuildingSearchEngine;
class ItemInformation;

class DeliveryManCharacter : public Character
{
    private:
        const BuildingSearchEngine& searchEngine;
        OptionalReference<AbstractProcessableBuilding> target;
        const ItemInformation& transportedItemConf;
        int transportedQuantity;
        bool goingHome;

    public:
        DeliveryManCharacter(
            CharacterManagerInterface& characterManager,
            const PathGeneratorInterface& pathGenerator,
            const BuildingSearchEngine& searchEngine,
            const CharacterInformation& conf,
            AbstractProcessableBuilding& issuer,
            const ItemInformation& transportedItemConf,
            const int transportedQuantity = 0
        );

        const ItemInformation& getTransportedItemConf() const;

        bool isEmpty() const;

        int getTransportedQuantity() const;

        void unload(const int quantity);

        void goHome();

        virtual void process(const CycleDate& date) override;
};

#endif // DELIVERYMANCHARACTER_HPP
