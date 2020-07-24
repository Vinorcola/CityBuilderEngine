#ifndef TARGETEDWALKERGENERATOR_HPP
#define TARGETEDWALKERGENERATOR_HPP

#include "engine/element/static/behavior/AbstractWalkerGenerator.hpp"
#include "engine/map/searchEngine/BuildingSearchCriteria.hpp"

class Character;
class CharacterInformation;
class ProcessableBuilding;
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
        const SearchEngine* searchEngine;
        BuildingSearchCriteria targetSearchCriteria;

    public:
        TargetedWalkerGenerator(
            ProcessableBuilding* issuer,
            const SearchEngine* searchEngine,
            const BuildingSearchCriteria* targetSearchCriteria,
            const CharacterInformation* walkerConf,
            const int generationInterval,
            const int maxWalkers = 1
        );

    protected:
        virtual void generate() override;
};

#endif // TARGETEDWALKERGENERATOR_HPP
