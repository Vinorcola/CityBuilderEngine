#ifndef CITYSTATUS_HPP
#define CITYSTATUS_HPP

#include <QtCore/QObject>

class CityStatus : public QObject
{
        Q_OBJECT

    private:
        int budget;
        int population;

    public:
        CityStatus(QObject* parent, const int initialBudget);

        int getBudget() const;

        int getPopulation() const;

        /**
         * @brief Update the population of the given delta.
         * @param delta A positive number for increasing, a negative number for decreasing.
         */
        void updatePopulation(const int delta);

    signals:
        void budgetChanged(const int budget);
        void populationChanged(const int population);
};

#endif // CITYSTATUS_HPP
