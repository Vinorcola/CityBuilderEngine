#ifndef IMMIGRANTCHARACTER_HPP
#define IMMIGRANTCHARACTER_HPP

#include "src/engine/map/dynamicElement/character/Character.hpp"

class AbstractProcessableBuilding;

class ImmigrantCharacter : public Character
{
    private:
        QWeakPointer<AbstractProcessableBuilding> target;

    public:
        ImmigrantCharacter(
            CharacterManagerInterface& characterManager,
            const PathGeneratorInterface& pathGenerator,
            const CharacterInformation& conf,
            const QSharedPointer<AbstractProcessableBuilding>& issuer,
            const QSharedPointer<AbstractProcessableBuilding>& target
        );

        virtual void process(const CycleDate& date) override;
};

#endif // IMMIGRANTCHARACTER_HPP
