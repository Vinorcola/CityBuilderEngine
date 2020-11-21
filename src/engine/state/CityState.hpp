#ifndef CITYSTATE_HPP
#define CITYSTATE_HPP

struct Date
{
    Date(int year, int month) :
        year(year),
        month(month)
    {}

    int year;
    int month;
};

struct CityState
{
    CityState(int budget, int population, Date date) :
        budget(budget),
        population(population),
        date(date)
    {}

    int budget;
    int population;
    Date date;
};

#endif // CITYSTATE_HPP
