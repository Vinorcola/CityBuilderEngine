#ifndef DELIVERYMANCHARACTER_HPP
#define DELIVERYMANCHARACTER_HPP

#include "src/engine/element/dynamic/Character.hpp"

class ItemInformation;
class MapSearchEngine;
class PathGenerator;
class PathInterface;

class DeliveryManCharacter : public Character
{
        Q_OBJECT

    private:
        const MapSearchEngine& searchEngine;
        const PathGenerator& pathGenerator;
        QPointer<ProcessableBuilding> target;
        const ItemInformation& transportedItemConf;
        int transportedQuantity;
        bool goingHome;

    public:
        DeliveryManCharacter(
            QObject* parent,
            const MapSearchEngine& searchEngine,
            const PathGenerator& pathGenerator,
            const CharacterInformation& conf,
            ProcessableBuilding& issuer,
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
