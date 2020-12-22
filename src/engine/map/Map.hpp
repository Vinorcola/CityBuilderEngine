#ifndef MAP_HPP
#define MAP_HPP

#include <QtCore/QSharedPointer>
#include <QtCore/QSize>

#include "src/engine/map/dynamicElement/DynamicElementRegistry.hpp"
#include "src/engine/map/path/PathGenerator.hpp"
#include "src/engine/map/staticElement/building/CivilianEntryPoint.hpp"
#include "src/engine/map/staticElement/StaticElementRegistry.hpp"
#include "src/engine/processing/AbstractProcessable.hpp"
#include "src/global/state/MapState.hpp"
#include "src/defines.hpp"

class CityLoader;
class Conf;
class Tile;

/**
 * @brief The city map.
 */
class Map : public AbstractProcessable
{
    public:
        explicit Map(
            const Conf& conf,
            CityLoader& loader,
            PopulationRegistryInterface& populationRegistry,
            WorkingPlaceRegistryInterface& workingPlaceRegistry
        );
        ~Map();

        QList<TileCoordinates> getShortestPathForRoad(const TileCoordinates& origin, const TileCoordinates& target) const;

        // States.
        MapState getState() const;
        QList<BuildingState> getBuildingsState() const;
        QList<NatureElementState> getNatureElementsState() const;
        QList<CharacterState> getCharactersState() const;

        // Elements
        void createBuilding(const BuildingInformation& conf, const TileCoordinates& leftCorner, Direction orientation);
        void createNatureElement(const NatureElementInformation& conf, const TileArea& area);

        // Map details
        bool isLocationValid(const TileCoordinates& coordinates) const;
        bool isAreaValid(const TileArea& area) const;
        bool isAreaConstructible(const TileArea& area) const;

        virtual void process(const CycleDate& date) override;

    private:
        Tile& getBestBuildingEntryPoint(const TileArea& area) const;
        static QHash<QString, owner<Tile*>> generateTiles(const QSize& size);

    private:
        const QSize size;
        QHash<QString, owner<Tile*>> tiles;
        QSharedPointer<CivilianEntryPoint> civilianEntryPoint;
        PathGenerator pathGenerator;
        StaticElementRegistry staticElements;
        DynamicElementRegistry dynamicElements;
};

#endif // MAP_HPP
