#include "CityStatus.hpp"

CityStatus::CityStatus(QObject* parent, const int initialBudget) :
    QObject(parent),
    budget(initialBudget),
    population(0)
{

}



int CityStatus::getBudget() const
{
    return budget;
}



int CityStatus::getPopulation() const
{
    return population;
}



void CityStatus::updatePopulation(const int delta)
{
    population += delta;

    emit populationChanged(population);
}
