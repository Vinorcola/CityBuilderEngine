#ifndef CITY_HPP
#define CITY_HPP

#include <QtCore/QList>

#include "src/engine/city/PopulationHandler.hpp"
#include "src/engine/map/Map.hpp"
#include "src/engine/processing/TimeCycleProcessor.hpp"
#include "src/global/state/CityState.hpp"

class CityLoader;
class Conf;

class City
{
    public:
        City(const Conf& conf, CityLoader& loader);

        TimeCycleProcessor& getProcessor();
        void createBuilding(const BuildingInformation& conf, const TileCoordinates& leftCorner, Direction orientation);

        bool isAreaConstructible(const TileArea& area) const;
        QList<TileCoordinates> getShortestPathForRoad(const TileCoordinates& origin, const TileCoordinates& target) const;

        MapState getMapState() const;
        CityState getCurrentState() const;
        QList<BuildingState> getBuildingsState() const;
        QList<NatureElementState> getNatureElementsState() const;
        QList<CharacterState> getCharactersState() const;

    private:
        const QString TITLE;
        TimeCycleProcessor processor;
        PopulationHandler population;
        Map map;
        int budget;
};

#endif // CITY_HPP
