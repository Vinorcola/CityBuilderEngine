#ifndef STUDENTCHARACTER_HPP
#define STUDENTCHARACTER_HPP

#include "src/engine/map/dynamicElement/character/Character.hpp"

class AbstractProcessableBuilding;

class StudentCharacter : public Character
{
    private:
        QWeakPointer<AbstractProcessableBuilding> target;

    public:
        StudentCharacter(
            CharacterDisposerInterface& characterManager,
            const PathGeneratorInterface& pathGenerator,
            const CharacterInformation& conf,
            const QSharedPointer<AbstractProcessableBuilding>& issuer,
            const QWeakPointer<AbstractProcessableBuilding>& target,
            owner<PathInterface*> path
        );

        virtual void process(const CycleDate& date) override;
};

#endif // STUDENTCHARACTER_HPP
