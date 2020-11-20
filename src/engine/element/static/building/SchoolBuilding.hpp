#ifndef SCHOOLBUILDING_HPP
#define SCHOOLBUILDING_HPP

#include <list>

#include "src/engine/element/static/building/AbstractProcessableBuilding.hpp"
#include "src/engine/processing/CycleDate.hpp"

class BuildingSearchEngine;
class Character;
class CharacterFactoryInterface;

/**
 * @brief A school building will generate student at a regular interval as long as there is a university accepting them.
 */
class SchoolBuilding : public AbstractProcessableBuilding
{
    private:
        const BuildingSearchEngine& searchEngine;
        CharacterFactoryInterface& characterFactory;
        CycleDate nextWalkerGenerationDate;

    public:
        SchoolBuilding(
            const BuildingSearchEngine& searchEngine,
            CharacterFactoryInterface& characterFactory,
            const BuildingInformation& conf,
            const MapArea& area,
            const MapCoordinates& entryPoint
        );

        virtual void init(const CycleDate& date) override;
        virtual void process(const CycleDate& date) override;

    private:
        /**
         * @brief Setup the next miner generation date.
         */
        void setupNextWalkerGenerationDate(const CycleDate& date);
};

#endif // SCHOOLBUILDING_HPP
