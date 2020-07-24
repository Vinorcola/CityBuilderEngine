#ifndef RANDOMWALKERGENERATOR_HPP
#define RANDOMWALKERGENERATOR_HPP

#include <QtCore/QList>
#include <QtCore/QPointer>

#include "engine/element/static/behavior/AbstractWalkerGenerator.hpp"

class AbstractProcessableStaticMapElement;
class DynamicElementInformation;

/**
 * @brief A wandering walker generator.
 *
 * Generates a walker that will take some road, walking randomly until it has walked for a certain distance.
 */
class RandomWalkerGenerator : public AbstractWalkerGenerator
{
        Q_OBJECT

    public:
        RandomWalkerGenerator(
            AbstractProcessableStaticMapElement* issuer,
            const DynamicElementInformation* walkerConf,
            const int generationInterval,
            const int maxWalkers = 1
        );
};

#endif // RANDOMWALKERGENERATOR_HPP
