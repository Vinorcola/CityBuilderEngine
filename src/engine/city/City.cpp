#include "City.hpp"

#include "src/engine/loader/CityLoader.hpp"



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

}
