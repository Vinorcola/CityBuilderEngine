#ifndef DELIVERYCHARACTER_HPP
#define DELIVERYCHARACTER_HPP

#include "src/engine/element/dynamic/Character.hpp"

class ItemInformation;
class PathGenerator;
class PathInterface;

class DeliveryCharacter : public Character
{
        Q_OBJECT

    private:
        const PathGenerator& pathGenerator;
        QPointer<ProcessableBuilding> target;
        const ItemInformation& transportedItemConf;
        int transportedQuantity;
        bool goingHome;

    public:
        DeliveryCharacter(
            QObject* parent,
            const PathGenerator& pathGenerator,
            const CharacterInformation& conf,
            ProcessableBuilding& issuer,
            ProcessableBuilding& target,
            owner<PathInterface*> path,
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

#endif // DELIVERYCHARACTER_HPP
