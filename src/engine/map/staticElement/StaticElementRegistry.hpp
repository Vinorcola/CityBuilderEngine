#ifndef STATICELEMENTREGISTRY_HPP
#define STATICELEMENTREGISTRY_HPP

#include <QtCore/QHash>
#include <QtCore/QList>
#include <QtCore/QSharedPointer>

#include "src/engine/map/staticElement/building/BuildingSearchEngine.hpp"
#include "src/engine/map/staticElement/natureElement/NatureElementSearchEngine.hpp"
#include "src/engine/map/staticElement/StaticElementFactory.hpp"
#include "src/engine/processing/AbstractProcessable.hpp"

class AbstractBuilding;
class CharacterInformation;
class CivilianEntryPoint;
class NatureElement;
class PathGeneratorInterface;
class WorkingPlaceRegistryInterface;

class StaticElementRegistry : public AbstractProcessable
{
        Q_DISABLE_COPY_MOVE(StaticElementRegistry)

    public:
        StaticElementRegistry(
            CharacterGeneratorInterface& characterGenerator,
            PopulationRegistryInterface& populationRegistry,
            WorkingPlaceRegistryInterface& workingPlaceRegistry,
            PathGeneratorInterface& pathGenerator,
            CivilianEntryPoint& civilianEntryPoint
        );

        // Search engines.
        const BuildingSearchEngine& getBuildingSearchEngine() const;

        // Element registration.
        void generateBuilding(const BuildingInformation& conf, const MapArea& area, Direction orientation);
        void generateProcessableBuilding(
            const BuildingInformation& conf,
            const MapArea& area,
            Direction orientation,
            const MapCoordinates& entryPoint
        );
        void generateNatureElement(const NatureElementInformation& conf, const MapArea& area);

        virtual void process(const CycleDate& date) override;

    private:
        WorkingPlaceRegistryInterface& workingPlaceRegistry;
        BuildingSearchEngine buildingSearchEngine;
        NatureElementSearchEngine natureElementSearchEngine;
        StaticElementFactory factory;
        QHash<AbstractBuilding*, QSharedPointer<AbstractBuilding>> buildings;
        QHash<NatureElement*, QSharedPointer<NatureElement>> natureElements;
        QHash<AbstractProcessable*, QSharedPointer<AbstractProcessable>> processableElements; ///< Contains any element that is processable (from `buildings` or `natureElements`)
};

#endif // STATICELEMENTREGISTRY_HPP
