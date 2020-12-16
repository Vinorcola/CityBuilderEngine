#ifndef HOUSEBUILDING_HPP
#define HOUSEBUILDING_HPP

#include <QtCore/QSharedPointer>

#include "src/engine/map/staticElement/building/AbstractProcessableBuilding.hpp"

class CharacterGeneratorInterface;
class ImmigrantGeneratorInterface;
class CivilianEntryPoint;
class PopulationRegistryInterface;

class HouseBuilding : public AbstractProcessableBuilding
{
    private:
        ImmigrantGeneratorInterface& immigrantGenerator;
        PopulationRegistryInterface& populationRegister;
        int inhabitants;
        bool hasRequestedInhabitants;

    private:
        HouseBuilding(
            ImmigrantGeneratorInterface& immigrantGenerator,
            PopulationRegistryInterface& populationRegister,
            const BuildingInformation& conf,
            const TileArea& area,
            Direction orientation,
            const TileCoordinates& entryPoint
        );

    public:
        static QSharedPointer<AbstractProcessableBuilding> Create(
            ImmigrantGeneratorInterface& immigrantGenerator,
            PopulationRegistryInterface& populationRegister,
            const BuildingInformation& conf,
            const TileArea& area,
            Direction orientation,
            const TileCoordinates& entryPoint
        );

        virtual void process(const CycleDate& date) override;
        virtual bool processInteraction(const CycleDate& date, Character& actor) override;

        virtual BuildingState getCurrentState() const override;
};

#endif // HOUSEBUILDING_HPP
