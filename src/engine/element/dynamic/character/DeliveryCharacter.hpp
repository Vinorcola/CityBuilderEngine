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
        int quantity;
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
            const int quantity = 0
        );

        void goHome();

        virtual void process(const CycleDate& date) override;
};

#endif // DELIVERYCHARACTER_HPP
