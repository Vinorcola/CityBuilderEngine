#ifndef STATICELEMENTHANDLER_HPP
#define STATICELEMENTHANDLER_HPP

#include <list>
#include <QtCore/QList>
#include <QtCore/QSet>

#include "src/engine/element/static/building/BuildingSearchEngine.hpp"
#include "src/engine/element/static/building/CivilianEntryPoint.hpp"
#include "src/engine/element/static/natureElement/NatureElementSearchEngine.hpp"
#include "src/engine/element/static/path/MapDetailsInterface.hpp"
#include "src/engine/element/static/path/PathGenerator.hpp"
#include "src/engine/state/BuildingState.hpp"
#include "src/engine/state/NatureElementState.hpp"
#include "src/defines.hpp"

class BuildingInformation;
class CharacterFactoryInterface;
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
            CivilianEntryPoint entryPoint;
            std::list<owner<AbstractBuilding*>> buildings;
            std::list<owner<NatureElement*>> natureElements;
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
        ~StaticElementHandler();

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
        void createBuilding(const BuildingInformation& conf, const MapArea& area);

        // Nature element generation.
        void createNatureElement(const NatureElementInformation& conf, const MapArea& area);

    private:
        void generateFarm(const BuildingInformation& conf, const MapArea& area);
        void generateHouse(const BuildingInformation& conf, const MapArea& area);
        void generateLaboratory(const BuildingInformation& conf, const MapArea& area);
        void generateProducer(const BuildingInformation& conf, const MapArea& area);
        void generateSanity(const BuildingInformation& conf, const MapArea& area);
        void generateSchool(const BuildingInformation& conf, const MapArea& area);
        void generateStorage(const BuildingInformation& conf, const MapArea& area);
        void generateRoad(const BuildingInformation& conf, const MapArea& area);
        MapCoordinates getBestBuildingEntryPoint(const MapArea& area) const;
        QString hashCoordinates(const MapCoordinates& coordinates) const;
        void registerBuildingInDetailsCache(const MapArea& area);
        void registerRoadInDetailsCache(const MapArea& area);
        void registerNatureElementInDetailsCache(const NatureElementInformation& conf, const MapArea& area);
};

#endif // STATICELEMENTHANDLER_HPP
