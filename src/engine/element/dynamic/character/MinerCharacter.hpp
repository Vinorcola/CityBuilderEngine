#ifndef MINERCHARACTER_HPP
#define MINERCHARACTER_HPP

#include <QtCore/QPointer>

#include "src/engine/element/dynamic/Character.hpp"
#include "src/defines.hpp"

class MinerCharacter : public Character
{
        Q_OBJECT

    private:
        bool goingHome;

    public:
        MinerCharacter(
            QObject* parent,
            CharacterManagerInterface& characterManager,
            const PathGeneratorInterface& pathGenerator,
            const CharacterInformation& conf,
            ProcessableBuilding& issuer,
            owner<PathInterface*> path
        );

        void goHome();

        virtual void process(const CycleDate& date) override;
};

#endif // MINERCHARACTER_HPP
