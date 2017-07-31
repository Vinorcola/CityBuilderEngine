#include "CityStatus.hpp"

CityStatus::CityStatus(QObject* parent, const int initialBudget) :
    QObject(parent),
    budget(initialBudget),
    population(0),
    freeHousingPlaces(0)
{

}



void CityStatus::updateFreeHousingPlaces(const int delta)
{
    freeHousingPlaces += delta;
}



void CityStatus::updatePopulation(const int delta)
{
    population += delta;
}
