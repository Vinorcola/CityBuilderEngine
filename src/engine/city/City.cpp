#include "City.hpp"

#include "src/engine/loader/CityLoader.hpp"
#include "src/engine/state/MapState.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/Conf.hpp"



City::State::State(const QString& title, int initialBudget) :
    title(title),
    budget(initialBudget)
{

}



City::City(const Conf& conf, CityLoader& loader) :
    population(),
    map(conf, loader, population, population),
    processor(population, loader.getStartDate()),
    staticElements(
        population,
        processor,
        map,
        dynamicElements,
        conf,
        loader.getMapEntryPoint()
    ),
    dynamicElements(
        processor,
        staticElements.getPathGenerator(),
        staticElements.getBuildingSearchEngine()
    ),
    currentState(loader.getTitle(), loader.getInitialBudget())
{
    // Load nature elements.
    for (const auto& natureElementInfo : loader.getInitialNatureElements()) {
        auto& natureElementConf(conf.getNatureElementConf(natureElementInfo.type));
        staticElements.createNatureElement(
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
        staticElements.createBuilding(
            buildingConf,
            buildingInfo.location,
            Direction::West // TODO: Set direction in YAML file.
        );
    }
}



TimeCycleProcessor& City::getProcessor()
{
    return processor;
}



void City::createBuilding(const BuildingInformation& conf, const MapCoordinates& leftCorner, Direction orientation)
{
    staticElements.createBuilding(conf, leftCorner, orientation);
}



bool City::isAreaConstructible(const MapArea& area) const
{
    return staticElements.isAreaConstructible(area);
}



QList<MapCoordinates> City::getShortestPathForRoad(const MapCoordinates& origin, const MapCoordinates& target) const
{
    return staticElements.getPathGenerator().generateShortestPathForRoad(origin, target);
}



MapState City::getMapState() const
{
    return map.getState();
}



CityState City::getCurrentState() const
{
    auto& date(processor.getCurrentDate());

    return {
        currentState.budget,
        population.getCurrentPopulation(),
        { date.getYear(), date.getMonth() },
    };
}



QList<BuildingState> City::getBuildingsState() const
{
    return staticElements.getBuildingsState();
}



QList<NatureElementState> City::getNatureElementsState() const
{
    return staticElements.getNatureElementsState();
}



QList<CharacterState> City::getCharactersState() const
{
    return dynamicElements.getCharactersState();
}
