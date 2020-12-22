#ifndef STATE_HPP
#define STATE_HPP

#include <QtCore/QList>

#include "src/global/state/BuildingState.hpp"
#include "src/global/state/CharacterState.hpp"
#include "src/global/state/CityState.hpp"
#include "src/global/state/NatureElementState.hpp"

struct State
{
    State(
        const CityState&& cityState,
        const QList<NatureElementState>& natureElements,
        const QList<BuildingState>& buildings,
        const QList<CharacterState>& characters
    ) :
        city(cityState),
        natureElements(natureElements),
        buildings(buildings),
        characters(characters)
    {}

    CityState city;
    QList<NatureElementState> natureElements;
    QList<BuildingState> buildings;
    QList<CharacterState> characters;
};

#endif // STATE_HPP
