#include "Engine.hpp"

#include "src/engine/city/City.hpp"
#include "src/engine/loader/CityLoader.hpp"



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
