#include "City.hpp"

#include "src/engine/loader/CityLoader.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/Conf.hpp"



City::City(const Conf& conf, CityLoader& loader) :
    title(loader.getTitle()),
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
    )
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
