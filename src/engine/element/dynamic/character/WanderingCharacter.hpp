#ifndef WANDERINGCHARACTER_HPP
#define WANDERINGCHARACTER_HPP

#include "src/engine/element/dynamic/character/Character.hpp"

class WanderingCharacter : public Character
{
        Q_OBJECT

    private:
        bool goingHome;

    public:
        WanderingCharacter(
            QObject* parent,
            CharacterManagerInterface& characterManager,
            const PathGeneratorInterface& pathGenerator,
            const CharacterInformation& conf,
            AbstractProcessableBuilding& issuer
        );

        void goHome();

        virtual void process(const CycleDate& date) override;
};

#endif // WANDERINGCHARACTER_HPP
