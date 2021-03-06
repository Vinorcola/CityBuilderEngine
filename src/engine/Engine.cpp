#include "Engine.hpp"

#include <cassert>

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

    connect(&city->getProcessor(), &TimeCycleProcessor::processFinished, [this]() {
        emit stateUpdated(getCurrentState());
    });
}



MapState Engine::getMapState() const
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
        city->getCharactersState(),
    };
}



bool Engine::isConstructible(const TileArea& area) const
{
    assert(city != nullptr);

    return city->isAreaConstructible(area);
}



QList<TileCoordinates> Engine::getShortestPathForRoad(const TileCoordinates& origin, const TileCoordinates& target) const
{
    assert(city != nullptr);

    return city->getShortestPathForRoad(origin, target);
}



void Engine::pause(const bool pause)
{
    assert(city != nullptr);

    city->getProcessor().pause(pause);
}



void Engine::setProcessorSpeedRatio(const qreal speedRatio)
{
    assert(city != nullptr);

    city->getProcessor().setSpeedRatio(speedRatio);
}



qreal Engine::getProcessorSpeedRatio() const
{
    assert(city != nullptr);

    return city->getProcessor().getSpeedRatio();
}



void Engine::forceNextProcess()
{
    assert(city != nullptr);

    city->getProcessor().forceNextProcess();
}



void Engine::createBuilding(const BuildingInformation& type, const TileCoordinates& leftCorner, Direction orientation)
{
    assert(city != nullptr);

    city->createBuilding(type, leftCorner, orientation);
}
