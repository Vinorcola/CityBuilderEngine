#include "PopulationHandler.hpp"

#include "src/engine/map/staticElement/building/AbstractProcessableBuilding.hpp"
#include "src/global/conf/BuildingInformation.hpp"



PopulationHandler::PopulationHandler() :
    previousPopulation(0),
    population(0),
    workingPlacesHasChanged(false),
    workingPlaces()
{

}



int PopulationHandler::getCurrentPopulation() const
{
    return population;
}



void PopulationHandler::registerPopulation(int quantity)
{
    population += quantity;
}



void PopulationHandler::unregisterPopulation(int quantity)
{
    population -= quantity;
}



void PopulationHandler::registerWorkingPlace(const QSharedPointer<AbstractProcessableBuilding>& building)
{
    workingPlaces.insert(building.get(), building);
    workingPlacesHasChanged = true;
}



void PopulationHandler::unregisterWorkingPlace(const QSharedPointer<AbstractProcessableBuilding>& building)
{
    workingPlaces.remove(building.get());
    workingPlacesHasChanged = true;
}



void PopulationHandler::process(const CycleDate& /*date*/)
{
    if (population != previousPopulation || workingPlacesHasChanged) {
        updateWorkerDistribution();

        previousPopulation = population;
        workingPlacesHasChanged = false;
    }
}



void PopulationHandler::updateWorkerDistribution()
{
    // For now, a dummy algorithm that fill up working place randomly.
    int remainingWorkers(population / 2);
    for (auto& workingPlace : workingPlaces) {
        int workPlaceWorkers(qMin(remainingWorkers, workingPlace->getConf().getMaxWorkers()));
        workingPlace->assignWorkers(workPlaceWorkers);
        remainingWorkers -= workPlaceWorkers;
    }
}
