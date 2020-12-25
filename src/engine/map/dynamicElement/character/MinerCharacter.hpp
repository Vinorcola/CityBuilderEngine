#ifndef MINERCHARACTER_HPP
#define MINERCHARACTER_HPP

#include "src/engine/map/dynamicElement/character/Character.hpp"

class MinerCharacter : public Character
{
    public:
        MinerCharacter(
            CharacterDisposerInterface& characterManager,
            const PathGeneratorInterface& pathGenerator,
            const CharacterInformation& conf,
            const QSharedPointer<AbstractProcessableBuilding>& issuer,
            QSharedPointer<PathInterface> path
        );

        void goHome();

        virtual void process(const CycleDate& date) override;

    private:
        bool goingHome;
        int workingCountDown;
};

#endif // MINERCHARACTER_HPP
