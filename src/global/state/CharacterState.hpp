#ifndef CHARACTERSTATE_HPP
#define CHARACTERSTATE_HPP

#include "src/global/geometry/DynamicElementCoordinates.hpp"
#include "src/global/CharacterStatus.hpp"
#include "src/global/Direction.hpp"

class CharacterInformation;

struct CharacterState
{
    CharacterState(
        qintptr id,
        const CharacterInformation& type,
        const DynamicElementCoordinates& position,
        Direction direction,
        CharacterStatus status,
        int stateVersion
    ) :
        id(id),
        type(type),
        position(position),
        direction(direction),
        status(status),
        stateVersion(stateVersion)
    {}

    CharacterState(const CharacterState& other) :
        id(other.id),
        type(other.type),
        position(other.position),
        direction(other.direction),
        status(other.status),
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

    qintptr id;
    const CharacterInformation& type;
    DynamicElementCoordinates position;
    Direction direction;
    CharacterStatus status;

    int stateVersion; ///< We use an int for the versionning of the view. Note that an overflow is not dramatic since we always compare versions using equality.
};

#endif // CHARACTERSTATE_HPP
