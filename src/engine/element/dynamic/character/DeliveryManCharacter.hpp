#ifndef DELIVERYMANCHARACTER_HPP
#define DELIVERYMANCHARACTER_HPP

#include "src/engine/element/dynamic/character/Character.hpp"

class ItemInformation;
class MapSearchEngine;
class AbstractProcessableBuilding;

class DeliveryManCharacter : public Character
{
        Q_OBJECT

    private:
        const MapSearchEngine& searchEngine;
        OptionalReference<AbstractProcessableBuilding> target;
        const ItemInformation& transportedItemConf;
        int transportedQuantity;
        bool goingHome;

    public:
        DeliveryManCharacter(
            QObject* parent,
            CharacterManagerInterface& characterManager,
            const PathGeneratorInterface& pathGenerator,
            const MapSearchEngine& searchEngine,
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
