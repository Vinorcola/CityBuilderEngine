#include "PopulationHandler.hpp"



PopulationHandler::State::State() :
    population(0)
{

}



PopulationHandler::PopulationHandler() :
    currentState(),
    newPopulation(0),
    workingPlaces()
{

}



int PopulationHandler::getCurrentPopulation() const
{
    return currentState.population;
}



void PopulationHandler::registerPopulation(int quantity)
{
    newPopulation += quantity;
}



void PopulationHandler::unregisterPopulation(int quantity)
{
    newPopulation -= quantity;
}



void PopulationHandler::registerWorkingPlace(const QSharedPointer<AbstractProcessableBuilding>& building)
{
    workingPlaces.insert(building.get(), building);
}



void PopulationHandler::unregisterWorkingPlace(const QSharedPointer<AbstractProcessableBuilding>& building)
{
    workingPlaces.remove(building.get());
}



void PopulationHandler::process(const CycleDate& /*date*/)
{
    if (newPopulation != currentState.population) {
        updateWorkerDistribution();
        currentState.population = newPopulation;
    }
}



void PopulationHandler::updateWorkerDistribution()
{
    // TODO
}
