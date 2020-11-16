#ifndef IMMIGRANTCHARACTER_HPP
#define IMMIGRANTCHARACTER_HPP

#include <QtCore/QObject>

#include "src/engine/element/dynamic/character/Character.hpp"

class AbstractProcessableBuilding;

class ImmigrantCharacter : public Character
{
    private:
        Reference<AbstractProcessableBuilding> target;

    public:
        ImmigrantCharacter(
            CharacterManagerInterface& characterManager,
            const PathGeneratorInterface& pathGenerator,
            const CharacterInformation& conf,
            AbstractProcessableBuilding& issuer,
            AbstractProcessableBuilding& target
        );

        virtual void process(const CycleDate& date) override;
};

#endif // IMMIGRANTCHARACTER_HPP
