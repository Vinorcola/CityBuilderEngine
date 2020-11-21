#ifndef POPULATIONREGISTRYINTERFACE_HPP
#define POPULATIONREGISTRYINTERFACE_HPP

/**
 * @brief An interface for a population registry.
 */
class PopulationRegistryInterface
{
    public:
        virtual ~PopulationRegistryInterface() {};

        virtual void registerPopulation(int quantity) = 0;
        virtual void unregisterPopulation(int quantity) = 0;
};

#endif // POPULATIONREGISTRYINTERFACE_HPP
