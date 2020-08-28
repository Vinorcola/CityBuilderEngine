#ifndef STUDENTCHARACTER_HPP
#define STUDENTCHARACTER_HPP

#include "src/engine/element/dynamic/Character.hpp"

class ProcessableBuilding;
class PathGenerator;

class StudentCharacter : public Character
{
        Q_OBJECT

    private:
        const PathGenerator& pathGenerator;
        QPointer<ProcessableBuilding> target;

    public:
        StudentCharacter(
            QObject* parent,
            const PathGenerator& pathGenerator,
            const CharacterInformation& conf,
            ProcessableBuilding& issuer,
            ProcessableBuilding& target,
            owner<PathInterface*> path
        );

        virtual void process(const CycleDate& date) override;
};

#endif // STUDENTCHARACTER_HPP
