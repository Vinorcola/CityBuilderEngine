#include "City.hpp"

#include "src/engine/loader/CityLoader.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/Conf.hpp"



City::State::State(const QString& title, int initialBudget) :
    title(title),
    budget(initialBudget)
{

}



City::City(const Conf& conf, CityLoader& loader) :
    map(loader.getMapSize()),
    processor(loader.getStartDate()),
    population(),
    staticElements(
        population,
        processor,
        map,
        dynamicElements,
        conf,
        loader.getMapEntryPoint()
    ),
    dynamicElements(
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
            MapArea(
                buildingInfo.location,
                buildingConf.getSize()
            )
        );
    }
}



TimeCycleProcessor& City::getProcessor()
{
    return processor;
}



void City::createBuilding(const BuildingInformation& conf, const MapArea& area)
{
    staticElements.createBuilding(conf, area);
}



const MapState& City::getMapState() const
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
