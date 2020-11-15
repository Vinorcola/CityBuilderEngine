#ifndef HOUSEBUILDING_HPP
#define HOUSEBUILDING_HPP

#include "src/engine/element/static/building/ProcessableBuilding.hpp"

class CharacterFactoryInterface;
class ImmigrantGeneratorInterface;
class MapEntryPoint;
class PopulationRegisterInterface;

class HouseBuilding : public ProcessableBuilding
{
        Q_OBJECT

    private:
        ImmigrantGeneratorInterface& immigrantGenerator;
        PopulationRegisterInterface& populationRegister;
        int inhabitants;

    public:
        HouseBuilding(
            QObject* parent,
            ImmigrantGeneratorInterface& immigrantGenerator,
            PopulationRegisterInterface& populationRegister,
            const BuildingInformation& conf,
            const MapArea& area,
            const MapCoordinates& entryPoint
        );

        virtual void init(const CycleDate& date);

        virtual void process(const CycleDate& date);

        virtual bool processInteraction(const CycleDate& date, Character& actor);
};

#endif // HOUSEBUILDING_HPP
