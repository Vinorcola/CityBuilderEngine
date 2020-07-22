#ifndef TARGETEDWALKERGENERATOR_HPP
#define TARGETEDWALKERGENERATOR_HPP

#include "engine/element/static/behavior/AbstractWalkerGenerator.hpp"
#include "engine/map/searchEngine/StaticSearchCriteria.hpp"

class AbstractDynamicMapElement;
class AbstractProcessableStaticMapElement;
class DynamicElementInformation;
class SearchEngine;

/**
 * @brief A targeted walker generator.
 *
 * The target is searched on walker generation according to the given search criteria. If no target is found, the walker
 * is still generated but without any target (it will just stay still).
 */
class TargetedWalkerGenerator : public AbstractWalkerGenerator
{
        Q_OBJECT

    private:
        const SearchEngine& searchEngine;
        StaticSearchCriteria targetSearchCriteria;

    public:
        TargetedWalkerGenerator(
            AbstractProcessableStaticMapElement* issuer,
            const SearchEngine& searchEngine,
            const StaticSearchCriteria* targetSearchCriteria,
            const DynamicElementInformation* walkerConf,
            const int generationInterval,
            const int maxWalkers = 1
        );

    protected:
        virtual void generate() override;
};

#endif // TARGETEDWALKERGENERATOR_HPP
