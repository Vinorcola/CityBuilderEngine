#ifndef MAPENTRYPOINT_HPP
#define MAPENTRYPOINT_HPP

#include <QtCore/QList>
#include <QtCore/QPointer>

#include "src/engine/element/static/building/ImmigrantGeneratorInterface.hpp"
#include "src/engine/element/static/building/ProcessableBuilding.hpp"
#include "src/engine/map/MapCoordinates.hpp"
#include "src/engine/processing/CycleDate.hpp"

class CharacterFactoryInterface;
class CharacterInformation;
class CycleDate;
class HouseBuilding;

/**
 * A map entry point.
 *
 * Map entry points are linked to a location on the border of the map. They can generate different types of characters.
 * Currently, it only supports immigrant charaters.
 */
class MapEntryPoint : public ProcessableBuilding, public ImmigrantGeneratorInterface
{
        Q_OBJECT

        const int MIN_IMMIGRANT_GENERATION_INTERVAL = 1;
        const int MAX_IMMIGRANT_GENERATION_INTERVAL = 90;

    private:
        CharacterFactoryInterface& characterFactory;
        const CharacterInformation& immigrantConf;
        CycleDate nextImmigrantGenerationDate;
        QList<QPointer<HouseBuilding>> immigrantRequestQueue;

    public:
        MapEntryPoint(
            QObject* parent,
            CharacterFactoryInterface& characterFactory,
            const BuildingInformation& conf,
            const MapCoordinates& location,
            const CharacterInformation& immigrantConf
        );

        virtual void requestImmigrant(HouseBuilding& requester) override;

        virtual void process(const CycleDate& date) override;

    private:
        void setupNextImmigrantGenerationDate(const CycleDate& currentDate);
};

#endif // MAPENTRYPOINT_HPP
