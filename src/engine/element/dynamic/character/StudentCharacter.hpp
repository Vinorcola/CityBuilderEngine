#ifndef STUDENTCHARACTER_HPP
#define STUDENTCHARACTER_HPP

#include "src/engine/element/dynamic/character/Character.hpp"

class ProcessableBuilding;

class StudentCharacter : public Character
{
        Q_OBJECT

    private:
        QPointer<ProcessableBuilding> target;

    public:
        StudentCharacter(
            QObject* parent,
            CharacterManagerInterface& characterManager,
            const PathGeneratorInterface& pathGenerator,
            const CharacterInformation& conf,
            ProcessableBuilding& issuer,
            ProcessableBuilding& target,
            owner<PathInterface*> path
        );

        virtual void process(const CycleDate& date) override;
};

#endif // STUDENTCHARACTER_HPP
