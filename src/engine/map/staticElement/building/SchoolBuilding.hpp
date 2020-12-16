#ifndef SCHOOLBUILDING_HPP
#define SCHOOLBUILDING_HPP

#include "src/engine/map/staticElement/building/behavior/WalkerGenerationBehavior.hpp"
#include "src/engine/map/staticElement/building/AbstractProcessableBuilding.hpp"
#include "src/engine/processing/CycleDate.hpp"

class BuildingSearchEngine;
class Character;
class CharacterGeneratorInterface;

/**
 * @brief A school building will generate student at a regular interval as long as there is a university accepting them.
 */
class SchoolBuilding : public AbstractProcessableBuilding
{
    private:
        const BuildingSearchEngine& searchEngine;
        CharacterGeneratorInterface& characterFactory;
        WalkerGenerationBehavior walkerGeneration;

    private:
        SchoolBuilding(
            const BuildingSearchEngine& searchEngine,
            CharacterGeneratorInterface& characterFactory,
            const BuildingInformation& conf,
            const TileArea& area,
            Direction orientation,
            const TileCoordinates& entryPoint
        );

    public:
        static QSharedPointer<AbstractProcessableBuilding> Create(
            const BuildingSearchEngine& searchEngine,
            CharacterGeneratorInterface& characterFactory,
            const BuildingInformation& conf,
            const TileArea& area,
            Direction orientation,
            const TileCoordinates& entryPoint
        );

        virtual void process(const CycleDate& date) override;
};

#endif // SCHOOLBUILDING_HPP
