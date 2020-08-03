#ifndef WANDERINGCHARACTER_HPP
#define WANDERINGCHARACTER_HPP

#include "src/engine/element/dynamic/Character.hpp"

class PathGenerator;

class WanderingCharacter : public Character
{
        Q_OBJECT

    private:
        const PathGenerator& pathGenerator;
        bool goingHome;

    public:
        WanderingCharacter(
            QObject* parent,
            const PathGenerator& pathGenerator,
            const CharacterInformation& conf,
            ProcessableBuilding& issuer
        );

        void goHome();

        virtual void process(const CycleDate& date) override;
};

#endif // WANDERINGCHARACTER_HPP
