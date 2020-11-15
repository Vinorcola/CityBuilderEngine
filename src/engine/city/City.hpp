#ifndef CITY_HPP
#define CITY_HPP

#include "src/engine/city/PopulationHandler.hpp"
#include "src/engine/element/dynamic/DynamicElementHandler.hpp"
#include "src/engine/element/static/StaticElementHandler.hpp"
#include "src/engine/map/Map.hpp"
#include "src/engine/processing/TimeCycleProcessor.hpp"

class CityLoader;
class Conf;

class City
{
    private:
        const QString title;
        Map map;
        TimeCycleProcessor processor;
        PopulationHandler population;
        StaticElementHandler staticElements;
        DynamicElementHandler dynamicElements;

    public:
        City(const Conf& conf, CityLoader& loader);

        /**
         * @brief Update the population of the given delta.
         * @param delta A positive number for increasing, a negative number for decreasing.
         */
        void updatePopulation(const int delta);
};

#endif // CITY_HPP
