#ifndef CITY_HPP
#define CITY_HPP

#include <QtCore/QList>

#include "src/engine/city/PopulationHandler.hpp"
#include "src/engine/element/dynamic/DynamicElementHandler.hpp"
#include "src/engine/element/static/StaticElementHandler.hpp"
#include "src/engine/map/Map.hpp"
#include "src/engine/processing/TimeCycleProcessor.hpp"
#include "src/engine/state/CityState.hpp"
#include "src/defines.hpp"

class CityLoader;
class Conf;

class City
{
    private:
        struct State {
            State(const QString& title, int initialBudget);

            const QString& title;
            int budget;
        };

    private:
        Map map;
        PopulationHandler population;
        TimeCycleProcessor processor;
        StaticElementHandler staticElements;
        DynamicElementHandler dynamicElements;
        State currentState;

    public:
        City(const Conf& conf, CityLoader& loader);

        TimeCycleProcessor& getProcessor();
        void createBuilding(const BuildingInformation& conf, const MapCoordinates& leftCorner, Direction orientation);

        bool isAreaConstructible(const MapArea& area) const;
        QList<MapCoordinates> getShortestPathForRoad(const MapCoordinates& origin, const MapCoordinates& target) const;

        const MapState& getMapState() const;
        CityState getCurrentState() const;
        QList<BuildingState> getBuildingsState() const;
        QList<NatureElementState> getNatureElementsState() const;
        QList<CharacterState> getCharactersState() const;
};

#endif // CITY_HPP
