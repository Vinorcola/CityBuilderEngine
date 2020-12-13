#ifndef MAP_HPP
#define MAP_HPP

#include <QtCore/QSharedPointer>
#include <QtCore/QSize>

#include "src/engine/map/dynamicElement/DynamicElementRegistry.hpp"
#include "src/engine/map/path/MapDetailsInterface.hpp"
#include "src/engine/map/path/PathGenerator.hpp"
#include "src/engine/map/staticElement/building/CivilianEntryPoint.hpp"
#include "src/engine/map/staticElement/StaticElementRegistry.hpp"
#include "src/engine/processing/AbstractProcessable.hpp"
#include "src/global/state/MapState.hpp"

class CityLoader;
class Conf;
class MapArea;
class MapCoordinates;

/**
 * @brief The city map.
 */
class Map : public AbstractProcessable, public MapDetailsInterface
{
    public:
        explicit Map(
            const Conf& conf,
            CityLoader& loader,
            PopulationRegistryInterface& populationRegistry,
            WorkingPlaceRegistryInterface& workingPlaceRegistry
        );

        const PathGenerator& getPathGenerator() const;

        // States.
        MapState getState() const;
        QList<BuildingState> getBuildingsState() const;
        QList<NatureElementState> getNatureElementsState() const;
        QList<CharacterState> getCharactersState() const;

        // Elements
        void createBuilding(const BuildingInformation& conf, const MapCoordinates& leftCorner, Direction orientation);
        void createNatureElement(const NatureElementInformation& conf, const MapArea& area);

        // Map details
        bool isLocationValid(const MapCoordinates& coordinates) const;
        bool isAreaValid(const MapArea& area) const;
        bool isAreaConstructible(const MapArea& area) const;
        virtual bool isLocationTraversable(const MapCoordinates& location) const override;
        virtual bool hasRoadAtLocation(const MapCoordinates& location) const override;
        virtual bool canConstructRoadAtLocation(const MapCoordinates& location) const override;

        virtual void process(const CycleDate& date) override;

    private:
        MapCoordinates getBestBuildingEntryPoint(const MapArea& area) const;

    private:
        struct DetailsCache {
            QSet<QString> nonConstructibleCoordinates;
            QSet<QString> nonTraversableCoordinates;
            QSet<QString> roadCoordinates;
        };

        const QSize size;
        QSharedPointer<CivilianEntryPoint> civilianEntryPoint;
        PathGenerator pathGenerator;
        StaticElementRegistry staticElements;
        DynamicElementRegistry dynamicElements;
        DetailsCache detailsCache;
};

#endif // MAP_HPP
