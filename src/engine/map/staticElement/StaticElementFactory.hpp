#ifndef STATICELEMENTFACTORY_HPP
#define STATICELEMENTFACTORY_HPP

#include <QtCore/QSharedPointer>

#include "src/global/Direction.hpp"

class AbstractBuilding;
class AbstractProcessableBuilding;
class BuildingInformation;
class BuildingSearchEngine;
class CharacterGeneratorInterface;
class CharacterInformation;
class ImmigrantGeneratorInterface;
class MapArea;
class MapCoordinates;
class NatureElementSearchEngine;
class PopulationRegistryInterface;
class StorageBuilding;

class StaticElementFactory
{
        Q_DISABLE_COPY_MOVE(StaticElementFactory)

    public:
        StaticElementFactory(
            CharacterGeneratorInterface& characterGenerator,
            ImmigrantGeneratorInterface& immigrantGenerator,
            PopulationRegistryInterface& populationRegister,
            const BuildingSearchEngine& buildingSearchEngine,
            const NatureElementSearchEngine& natureElementSearchEngine
        );

        QSharedPointer<AbstractProcessableBuilding> generateFarm(
            const BuildingInformation& conf,
            const MapArea& area,
            Direction orientation,
            const MapCoordinates& entryPoint
        );

        QSharedPointer<AbstractProcessableBuilding> generateHouse(
            const BuildingInformation& conf,
            const MapArea& area,
            Direction orientation,
            const MapCoordinates& entryPoint
        );

        QSharedPointer<AbstractProcessableBuilding> generateLaboratory(
            const BuildingInformation& conf,
            const MapArea& area,
            Direction orientation,
            const MapCoordinates& entryPoint
        );

        QSharedPointer<AbstractProcessableBuilding> generateProducer(
            const BuildingInformation& conf,
            const MapArea& area,
            Direction orientation,
            const MapCoordinates& entryPoint
        );

        QSharedPointer<AbstractBuilding> generateRoad(
            const BuildingInformation& conf,
            const MapArea& area,
            Direction orientation
        );

        QSharedPointer<AbstractProcessableBuilding> generateSanity(
            const BuildingInformation& conf,
            const MapArea& area,
            Direction orientation,
            const MapCoordinates& entryPoint
        );

        QSharedPointer<AbstractProcessableBuilding> generateSchool(
            const BuildingInformation& conf,
            const MapArea& area,
            Direction orientation,
            const MapCoordinates& entryPoint
        );

        QSharedPointer<StorageBuilding> generateStorage(
            const BuildingInformation& conf,
            const MapArea& area,
            Direction orientation,
            const MapCoordinates& entryPoint
        );

    private:
        CharacterGeneratorInterface& characterGenerator;
        ImmigrantGeneratorInterface& immigrantGenerator;
        PopulationRegistryInterface& populationRegister;
        const BuildingSearchEngine& buildingSearchEngine;
        const NatureElementSearchEngine& natureElementSearchEngine;
};

#endif // STATICELEMENTFACTORY_HPP
