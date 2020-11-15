#ifndef STATICELEMENTHANDLER_HPP
#define STATICELEMENTHANDLER_HPP

#include <list>
#include <QtCore/QSet>

#include "src/engine/element/static/building/BuildingSearchEngine.hpp"
#include "src/engine/element/static/natureElement/NatureElementSearchEngine.hpp"
#include "src/defines.hpp"

class Building;
class BuildingInformation;
class CharacterFactoryInterface;
class FarmBuilding;
class HouseBuilding;
class ImmigrantGeneratorInterface;
class LaboratoryBuilding;
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

class StaticElementHandler
{
    private:
        struct State {
            std::list<owner<Building*>> buildings;
            std::list<owner<NatureElement*>> natureElements;
        };
        struct DetailsCache {
            QSet<QString> nonConstructibleCoordinates;
            QSet<QString> nonTraversableCoordinates;
            QSet<QString> roadCoordinates;
        };

    private:
        CharacterFactoryInterface& characterFactory;
        ImmigrantGeneratorInterface& immigrantGenerator;
        PopulationHandler& populationHandler;
        TimeCycleProcessor& processor;
        BuildingSearchEngine buildingSearchEngine;
        NatureElementSearchEngine natureElementSearchEngine;
        State currentState;
        DetailsCache detailsCache;

    public:
        explicit StaticElementHandler(
            CharacterFactoryInterface& characterFactory,
            ImmigrantGeneratorInterface& immigrantGenerator,
            PopulationHandler& populationHandler,
            TimeCycleProcessor& processor
        );
        ~StaticElementHandler();

        FarmBuilding& generateFarm(const BuildingInformation& conf, const MapArea& area);
        HouseBuilding& generateHouse(const BuildingInformation& conf, const MapArea& area);
        LaboratoryBuilding& generateLaboratory(const BuildingInformation& conf, const MapArea& area);
        ProducerBuilding& generateProducer(const BuildingInformation& conf, const MapArea& area);
        SanityBuilding& generateSanity(const BuildingInformation& conf, const MapArea& area);
        SchoolBuilding& generateSchool(const BuildingInformation& conf, const MapArea& area);
        StorageBuilding& generateStorage(const BuildingInformation& conf, const MapArea& area);
        Road& generateRoad(const BuildingInformation& conf, const MapCoordinates& location);

    private:
        MapCoordinates getBestBuildingEntryPoint(const MapArea& area) const;
        QString hashCoordinates(const MapCoordinates& coordinates) const;
        void registerBuildingInDetailsCache(const MapArea& area);
        void registerRoadInDetailsCache(const MapCoordinates& location);
};

#endif // STATICELEMENTHANDLER_HPP
