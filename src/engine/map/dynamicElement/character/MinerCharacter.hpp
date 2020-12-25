#ifndef MINERCHARACTER_HPP
#define MINERCHARACTER_HPP

#include "src/engine/map/dynamicElement/character/Character.hpp"

class NatureElementSearchEngine;

class MinerCharacter : public Character
{
    public:
        MinerCharacter(
            CharacterDisposerInterface& characterManager,
            const PathGeneratorInterface& pathGenerator,
            const NatureElementSearchEngine& searchEngine,
            const CharacterInformation& conf,
            const QSharedPointer<AbstractProcessableBuilding>& issuer,
            QSharedPointer<PathInterface> path
        );

        void goHome();

        virtual void process(const CycleDate& date) override;

    protected:
        virtual CharacterStatus getCurrentStatus() const override;

    private:
        const NatureElementSearchEngine& searchEngine;
        bool goingHome;
        int workingCountDown;
        CharacterStatus status;
};

#endif // MINERCHARACTER_HPP
