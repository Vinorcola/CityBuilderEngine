#ifndef CHARACTERSTATE_HPP
#define CHARACTERSTATE_HPP

#include "src/engine/map/MapCoordinates.hpp"
#include "src/global/Direction.hpp"

class CharacterInformation;

struct CharacterState
{
    CharacterState(
        const CharacterInformation& type,
        const MapCoordinates& position,
        Direction direction,
        int stateVersion
    ) :
        type(type),
        position(position),
        direction(direction),
        stateVersion(stateVersion)
    {}

    CharacterState(const CharacterState& other) :
        type(other.type),
        position(other.position),
        direction(other.direction),
        stateVersion(other.stateVersion)
    {}

    CharacterState& operator=(const CharacterState& other)
    {
        if (this != &other) {
            this->~CharacterState();
            new(this) CharacterState(other);
        }

        return *this;
    }

    const CharacterInformation& type;
    MapCoordinates position;
    Direction direction;

    int stateVersion; ///< We use an int for the versionning of the view. Note that an overflow is not dramatic since we always compare versions using equality.
};

#endif // CHARACTERSTATE_HPP
