#ifndef MINERCHARACTER_HPP
#define MINERCHARACTER_HPP

#include <QtCore/QPointer>

#include "src/engine/element/dynamic/Character.hpp"
#include "src/defines.hpp"

class NatureElement;
class PathGenerator;

class MinerCharacter : public Character
{
        Q_OBJECT

    private:
        const PathGenerator& pathGenerator;
        bool goingHome;

    public:
        MinerCharacter(
            QObject* parent,
            const PathGenerator& pathGenerator,
            const CharacterInformation& conf,
            ProcessableBuilding& issuer,
            owner<PathInterface*> path
        );

        void goHome();

        virtual void process(const CycleDate& date) override;

    signals:
        void hasFinishedHarvest();
};

#endif // MINERCHARACTER_HPP
