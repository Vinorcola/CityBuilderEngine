#ifndef IMMIGRANTCHARACTER_HPP
#define IMMIGRANTCHARACTER_HPP

#include <QtCore/QObject>

#include "src/engine/element/dynamic/Character.hpp"

class ProcessableBuilding;

class ImmigrantCharacter : public Character
{
    private:
        QPointer<ProcessableBuilding> target;

    public:
        ImmigrantCharacter(
            QObject* parent,
            CharacterManagerInterface& characterManager,
            const PathGeneratorInterface& pathGenerator,
            const CharacterInformation& conf,
            ProcessableBuilding& issuer,
            ProcessableBuilding& target
        );

        virtual void process(const CycleDate& date) override;
};

#endif // IMMIGRANTCHARACTER_HPP
