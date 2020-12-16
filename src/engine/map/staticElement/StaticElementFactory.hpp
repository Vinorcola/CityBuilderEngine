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
class NatureElementSearchEngine;
class PopulationRegistryInterface;
class StorageBuilding;
class TileArea;
class TileCoordinates;

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
            const TileArea& area,
            Direction orientation,
            const TileCoordinates& entryPoint
        );

        QSharedPointer<AbstractProcessableBuilding> generateHouse(
            const BuildingInformation& conf,
            const TileArea& area,
            Direction orientation,
            const TileCoordinates& entryPoint
        );

        QSharedPointer<AbstractProcessableBuilding> generateLaboratory(
            const BuildingInformation& conf,
            const TileArea& area,
            Direction orientation,
            const TileCoordinates& entryPoint
        );

        QSharedPointer<AbstractProcessableBuilding> generateProducer(
            const BuildingInformation& conf,
            const TileArea& area,
            Direction orientation,
            const TileCoordinates& entryPoint
        );

        QSharedPointer<AbstractBuilding> generateRoad(
            const BuildingInformation& conf,
            const TileArea& area,
            Direction orientation
        );

        QSharedPointer<AbstractProcessableBuilding> generateSanity(
            const BuildingInformation& conf,
            const TileArea& area,
            Direction orientation,
            const TileCoordinates& entryPoint
        );

        QSharedPointer<AbstractProcessableBuilding> generateSchool(
            const BuildingInformation& conf,
            const TileArea& area,
            Direction orientation,
            const TileCoordinates& entryPoint
        );

        QSharedPointer<StorageBuilding> generateStorage(
            const BuildingInformation& conf,
            const TileArea& area,
            Direction orientation,
            const TileCoordinates& entryPoint
        );

    private:
        CharacterGeneratorInterface& characterGenerator;
        ImmigrantGeneratorInterface& immigrantGenerator;
        PopulationRegistryInterface& populationRegister;
        const BuildingSearchEngine& buildingSearchEngine;
        const NatureElementSearchEngine& natureElementSearchEngine;
};

#endif // STATICELEMENTFACTORY_HPP
