#include "Engine.hpp"

#include <cassert>

#include "src/engine/city/City.hpp"
#include "src/engine/loader/CityLoader.hpp"
#include "src/engine/state/State.hpp"



Engine::Engine(const Conf& conf) :
    conf(conf),
    city(nullptr)
{

}



Engine::~Engine()
{
    if (city) {
        delete city;
    }
}



void Engine::loadCity(const QString& cityFilePath)
{
    if (city) {
        delete city;
    }

    CityLoader loader(cityFilePath);
    city = new City(conf, loader);
}



const MapState& Engine::getMapState() const
{
    assert(city != nullptr);

    return city->getMapState();
}



State Engine::getCurrentState() const
{
    assert(city != nullptr);

    return {
        city->getCurrentState(),
        city->getNatureElementsState(),
        city->getBuildingsState(),
    };
}
