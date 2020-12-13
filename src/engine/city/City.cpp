#include "City.hpp"

#include "src/engine/loader/CityLoader.hpp"
#include "src/engine/state/CityState.hpp"
#include "src/engine/state/MapState.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/Conf.hpp"



City::City(const Conf& conf, CityLoader& loader) :
    TITLE(loader.getTitle()),
    processor(loader.getStartDate()),
    population(),
    map(conf, loader, population, population),
    budget(loader.getInitialBudget())
{
    // Load nature elements.
    for (const auto& natureElementInfo : loader.getInitialNatureElements()) {
        auto& natureElementConf(conf.getNatureElementConf(natureElementInfo.type));
        map.createNatureElement(
            natureElementConf,
            MapArea(
                natureElementInfo.location,
                MapSize(1) // For now, only single tile nature elements are supported.
            )
        );
    }

    // Load buildings.
    for (const auto& buildingInfo : loader.getInitialBuildings()) {
        auto& buildingConf(conf.getBuildingConf(buildingInfo.type));
        map.createBuilding(
            buildingConf,
            buildingInfo.location,
            Direction::West // TODO: Set direction in YAML file.
        );
    }

    processor.registerProcessable(map);
    processor.registerProcessable(population);
}



TimeCycleProcessor& City::getProcessor()
{
    return processor;
}



void City::createBuilding(const BuildingInformation& conf, const MapCoordinates& leftCorner, Direction orientation)
{
    map.createBuilding(conf, leftCorner, orientation);
}



bool City::isAreaConstructible(const MapArea& area) const
{
    return map.isAreaConstructible(area);
}



QList<MapCoordinates> City::getShortestPathForRoad(const MapCoordinates& origin, const MapCoordinates& target) const
{
    return map.getPathGenerator().generateShortestPathForRoad(origin, target);
}



MapState City::getMapState() const
{
    return map.getState();
}



CityState City::getCurrentState() const
{
    auto& date(processor.getCurrentDate());

    return {
        budget,
        population.getCurrentPopulation(),
        { date.getYear(), date.getMonth() },
    };
}



QList<BuildingState> City::getBuildingsState() const
{
    return map.getBuildingsState();
}



QList<NatureElementState> City::getNatureElementsState() const
{
    return map.getNatureElementsState();
}



QList<CharacterState> City::getCharactersState() const
{
    return map.getCharactersState();
}
