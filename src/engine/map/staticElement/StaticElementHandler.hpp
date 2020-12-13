#ifndef STATICELEMENTHANDLER_HPP
#define STATICELEMENTHANDLER_HPP

#include <QtCore/QHash>
#include <QtCore/QSet>
#include <QtCore/QSharedPointer>

#include "src/engine/map/path/MapDetailsInterface.hpp"
#include "src/engine/map/path/PathGenerator.hpp"
#include "src/engine/map/staticElement/building/BuildingSearchEngine.hpp"
#include "src/engine/map/staticElement/natureElement/NatureElementSearchEngine.hpp"
#include "src/engine/state/BuildingState.hpp"
#include "src/engine/state/NatureElementState.hpp"
#include "src/global/Direction.hpp"
#include "src/defines.hpp"

class AbstractBuilding;
class BuildingInformation;
class CharacterFactoryInterface;
class CivilianEntryPoint;
class Conf;
class FarmBuilding;
class HouseBuilding;
class ImmigrantGeneratorInterface;
class LaboratoryBuilding;
class Map;
class MapArea;
class MapCoordinates;
class NatureElement;
class PopulationHandler;
class ProducerBuilding;
class QString;
class Road;
class SanityBuilding;
class SchoolBuilding;
class StorageBuilding;
class TimeCycleProcessor;

class StaticElementHandler : public MapDetailsInterface
{
    private:
        struct State {
            State(
                CharacterFactoryInterface& characterFactory,
                const Conf& conf,
                const MapCoordinates& entryPointLocation
            );
            QSharedPointer<CivilianEntryPoint> entryPoint;
            QHash<AbstractBuilding*, QSharedPointer<AbstractBuilding>> buildings;
            QHash<NatureElement*, QSharedPointer<NatureElement>> natureElements;
        };
        struct DetailsCache {
            QSet<QString> nonConstructibleCoordinates;
            QSet<QString> nonTraversableCoordinates;
            QSet<QString> roadCoordinates;
        };

    private:
        PopulationHandler& populationHandler;
        TimeCycleProcessor& processor;
        const Map& map;
        CharacterFactoryInterface& characterFactory;
        State currentState;
        DetailsCache detailsCache;
        PathGenerator pathGenerator;
        BuildingSearchEngine buildingSearchEngine;
        NatureElementSearchEngine natureElementSearchEngine;

    public:
        /**
         * Important: the `characterFactory` reference points to a non-initialized yet factory. Do not use the factory
         * within the constructor!
         */
        StaticElementHandler(
            PopulationHandler& populationHandler,
            TimeCycleProcessor& processor,
            const Map& map,
            CharacterFactoryInterface& characterFactory,
            const Conf& conf,
            const MapCoordinates& mapEntryPointLocation
        );

        const PathGenerator& getPathGenerator() const;

        // Search engines.
        const BuildingSearchEngine& getBuildingSearchEngine() const;
        const NatureElementSearchEngine& getNatureElementSearchEngine() const;

        // Map details.
        bool isLocationConstructible(const MapCoordinates& location) const;
        bool isAreaConstructible(const MapArea& area) const;
        virtual bool isLocationTraversable(const MapCoordinates& location) const override;
        virtual bool hasRoadAtLocation(const MapCoordinates& location) const override;
        virtual bool canConstructRoadAtLocation(const MapCoordinates& location) const override;

        // State
        QList<BuildingState> getBuildingsState() const;
        QList<NatureElementState> getNatureElementsState() const;

        // Building generation.
        void createBuilding(const BuildingInformation& conf, const MapCoordinates& leftCorner, Direction orientation);

        // Nature element generation.
        void createNatureElement(const NatureElementInformation& conf, const MapArea& area);

    private:
        void generateFarm(const BuildingInformation& conf, const MapArea& area, Direction orientation);
        void generateHouse(const BuildingInformation& conf, const MapArea& area, Direction orientation);
        void generateLaboratory(const BuildingInformation& conf, const MapArea& area, Direction orientation);
        void generateProducer(const BuildingInformation& conf, const MapArea& area, Direction orientation);
        void generateSanity(const BuildingInformation& conf, const MapArea& area, Direction orientation);
        void generateSchool(const BuildingInformation& conf, const MapArea& area, Direction orientation);
        void generateStorage(const BuildingInformation& conf, const MapArea& area, Direction orientation);
        void generateRoad(const BuildingInformation& conf, const MapArea& area, Direction orientation);
        MapCoordinates getBestBuildingEntryPoint(const MapArea& area) const;
        void registerBuildingInDetailsCache(const MapArea& area);
        void registerRoadInDetailsCache(const MapArea& area);
        void registerNatureElementInDetailsCache(const NatureElementInformation& conf, const MapArea& area);
};

#endif // STATICELEMENTHANDLER_HPP
