#ifndef POPULATIONREGISTERINTERFACE_HPP
#define POPULATIONREGISTERINTERFACE_HPP

/**
 * @brief An interface for a population register.
 */
class PopulationRegisterInterface
{
    public:
        virtual ~PopulationRegisterInterface() {};

        virtual void registerPopulation(int quantity) = 0;
        virtual void unregisterPopulation(int quantity) = 0;
};

#endif // POPULATIONREGISTERINTERFACE_HPP
