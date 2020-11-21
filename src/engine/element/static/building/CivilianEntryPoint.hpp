#ifndef MAPENTRYPOINT_HPP
#define MAPENTRYPOINT_HPP

#include <QtCore/QSharedPointer>

#include "src/engine/element/static/building/AbstractProcessableBuilding.hpp"
#include "src/engine/element/static/building/ImmigrantGeneratorInterface.hpp"
#include "src/engine/map/MapCoordinates.hpp"
#include "src/engine/processing/CycleDate.hpp"

class CharacterFactoryInterface;
class CharacterInformation;
class CycleDate;

/**
 * @brief A civilian entry point on the map.
 *
 * Map entry points are linked to a location on the border of the map. They can generate different types of characters.
 * Currently, it only supports immigrant charaters.
 */
class CivilianEntryPoint : public AbstractProcessableBuilding, public ImmigrantGeneratorInterface
{
        const int MIN_IMMIGRANT_GENERATION_INTERVAL = 1;
        const int MAX_IMMIGRANT_GENERATION_INTERVAL = 90;

    private:
        CharacterFactoryInterface& characterFactory;
        const CharacterInformation& immigrantConf;
        CycleDate nextImmigrantGenerationDate;
        QList<QWeakPointer<AbstractProcessableBuilding>> immigrantRequestQueue;

    private:
        CivilianEntryPoint(
            CharacterFactoryInterface& characterFactory,
            const BuildingInformation& conf,
            const MapCoordinates& location,
            const CharacterInformation& immigrantConf
        );

    public:
        static QSharedPointer<CivilianEntryPoint> Create(
            CharacterFactoryInterface& characterFactory,
            const BuildingInformation& conf,
            const MapCoordinates& location,
            const CharacterInformation& immigrantConf
        );

        virtual void requestImmigrant(const QWeakPointer<AbstractProcessableBuilding>& requester) override;

        virtual void process(const CycleDate& date) override;

    private:
        void setupNextImmigrantGenerationDate(const CycleDate& currentDate);
};

#endif // MAPENTRYPOINT_HPP
