#ifndef STUDENTCHARACTER_HPP
#define STUDENTCHARACTER_HPP

#include "src/engine/element/dynamic/character/Character.hpp"

class AbstractProcessableBuilding;

class StudentCharacter : public Character
{
    private:
        Reference<AbstractProcessableBuilding> target;

    public:
        StudentCharacter(
            CharacterManagerInterface& characterManager,
            const PathGeneratorInterface& pathGenerator,
            const CharacterInformation& conf,
            AbstractProcessableBuilding& issuer,
            AbstractProcessableBuilding& target,
            owner<PathInterface*> path
        );

        virtual void process(const CycleDate& date) override;
};

#endif // STUDENTCHARACTER_HPP
