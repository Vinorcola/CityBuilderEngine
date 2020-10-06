#ifndef IMMIGRANTCHARACTER_HPP
#define IMMIGRANTCHARACTER_HPP

#include <QtCore/QObject>

#include "src/engine/element/dynamic/Character.hpp"

class CharacterInformation;
class MapCoordinates;
class PathGenerator;
class ProcessableBuilding;

class ImmigrantCharacter : public Character
{
    public:
        ImmigrantCharacter(
            QObject* parent,
            const PathGenerator& pathGenerator,
            const CharacterInformation& conf,
            const MapCoordinates& initialLocation,
            ProcessableBuilding& issuer
        );

        virtual void process(const CycleDate& date) override;
};

#endif // IMMIGRANTCHARACTER_HPP
