#ifndef STATE_HPP
#define STATE_HPP

#include <QtCore/QList>

#include "src/engine/state/BuildingState.hpp"
#include "src/engine/state/CityState.hpp"
#include "src/engine/state/NatureElementState.hpp"

struct State
{
    State(
        const CityState&& cityState,
        const QList<NatureElementState>& natureElements,
        const QList<BuildingState>& buildings
    ) :
        city(cityState),
        natureElements(natureElements),
        buildings(buildings)
    {}

    CityState city;
    QList<NatureElementState> natureElements;
    QList<BuildingState> buildings;
};

#endif // STATE_HPP
