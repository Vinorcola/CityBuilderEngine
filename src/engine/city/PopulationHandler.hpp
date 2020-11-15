#ifndef POPULATIONHANDLER_HPP
#define POPULATIONHANDLER_HPP

#include <list>

#include "src/engine/city/PopulationRegisterInterface.hpp"
#include "src/engine/processing/AbstractProcessable.hpp"

class AbstractProcessableBuilding;

/**
 * @brief Handles the population and the worker distribution.
 */
class PopulationHandler : public AbstractProcessable, public PopulationRegisterInterface
{
    private:
        struct State{
            State();
            int population;
        };

    private:
        State currentState;
        int newPopulation;
        std::list<AbstractProcessableBuilding*> workingPlaces;

    public:
        PopulationHandler();

        virtual void registerPopulation(int quantity) override;
        virtual void unregisterPopulation(int quantity) override;

        void registerWorkingPlace(AbstractProcessableBuilding& building);
        void unregisterWorkingPlace(AbstractProcessableBuilding& building);

        virtual void process(const CycleDate& date) override;

    private:
        void updateWorkerDistribution();
};

#endif // POPULATIONHANDLER_HPP
