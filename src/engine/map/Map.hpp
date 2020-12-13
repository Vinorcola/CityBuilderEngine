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

class Conf;
class CityLoader;
class MapArea;
class MapCoordinates;
class MapState;

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

        MapState getState() const;

        // Map details
        bool isLocationValid(const MapCoordinates& coordinates) const;
        bool isAreaValid(const MapArea& area) const;
        virtual bool isLocationTraversable(const MapCoordinates& location) const override;
        virtual bool hasRoadAtLocation(const MapCoordinates& location) const override;
        virtual bool canConstructRoadAtLocation(const MapCoordinates& location) const override;

        virtual void process(const CycleDate& date);

    private:
        const QSize size;
        QSharedPointer<CivilianEntryPoint> civilianEntryPoint;
        PathGenerator pathGenerator;
        StaticElementRegistry staticElements;
        DynamicElementRegistry dynamicElements;
};

#endif // MAP_HPP
