#ifndef POPULATIONHANDLER_HPP
#define POPULATIONHANDLER_HPP

#include <QtCore/QHash>
#include <QtCore/QSharedPointer>

#include "src/engine/city/PopulationRegistryInterface.hpp"
#include "src/engine/processing/AbstractProcessable.hpp"

class AbstractProcessableBuilding;

/**
 * @brief Handles the population and the worker distribution.
 */
class PopulationHandler : public AbstractProcessable, public PopulationRegistryInterface
{
    private:
        struct State{
            State();

            int population;
        };

    private:
        State currentState;
        int newPopulation;
        QHash<AbstractProcessableBuilding*, QSharedPointer<AbstractProcessableBuilding>> workingPlaces;

    public:
        PopulationHandler();

        int getCurrentPopulation() const;

        virtual void registerPopulation(int quantity) override;
        virtual void unregisterPopulation(int quantity) override;

        void registerWorkingPlace(const QSharedPointer<AbstractProcessableBuilding>& building);
        void unregisterWorkingPlace(const QSharedPointer<AbstractProcessableBuilding>& building);

        virtual void process(const CycleDate& date) override;

    private:
        void updateWorkerDistribution();
};

#endif // POPULATIONHANDLER_HPP
