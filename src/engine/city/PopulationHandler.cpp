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



void PopulationHandler::registerPopulation(int quantity)
{
    newPopulation += quantity;
}



void PopulationHandler::unregisterPopulation(int quantity)
{
    newPopulation -= quantity;
}



void PopulationHandler::registerWorkingPlace(ProcessableBuilding& building)
{
    workingPlaces.push_back(&building);
}



void PopulationHandler::unregisterWorkingPlace(ProcessableBuilding& building)
{
    workingPlaces.remove(&building);
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
