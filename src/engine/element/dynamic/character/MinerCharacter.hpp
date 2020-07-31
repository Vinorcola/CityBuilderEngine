#ifndef MINERCHARACTER_HPP
#define MINERCHARACTER_HPP

#include <QtCore/QPointer>

#include "src/engine/element/dynamic/Character.hpp"
#include "src/defines.hpp"

class NatureElement;

class MinerCharacter : public Character
{
        Q_OBJECT

    public:
        MinerCharacter(
            QObject* parent,
            const CharacterInformation& conf,
            ProcessableBuilding& issuer,
            owner<PathInterface*> path
        );

        void goHome(owner<PathInterface*> path);

        virtual void process(const CycleDate& date) override;

    signals:
        void hasFinishedHarvest();
};

#endif // MINERCHARACTER_HPP
