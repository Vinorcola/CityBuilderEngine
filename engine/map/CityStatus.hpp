#ifndef CITYSTATUS_HPP
#define CITYSTATUS_HPP


class CityStatus
{
    private:
        int budget;
        int population;
        int freeHousingPlaces;

    public:
        CityStatus(const int initialBudget);

        /**
         * @brief Update the number of free housing of the given delta.
         * @param delta A positive number for increasing, a negative number for decreasing.
         */
        void updateFreeHousingPlaces(const int delta);

        /**
         * @brief Update the population of the given delta.
         * @param delta A positive number for increasing, a negative number for decreasing.
         */
        void updatePopulation(const int delta);
};

#endif // CITYSTATUS_HPP
