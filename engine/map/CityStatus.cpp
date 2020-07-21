#include "CityStatus.hpp"



CityStatus::CityStatus(const int initialBudget) :
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
