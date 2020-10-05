#ifndef MAPENTRYPOINT_HPP
#define MAPENTRYPOINT_HPP

#include <QtCore/QList>
#include <QtCore/QPointer>

#include "src/engine/map/MapCoordinates.hpp"
#include "src/engine/processing/CycleDate.hpp"
#include "src/engine/processing/AbstractProcessable.hpp"

class Character;
class CharacterFactoryInterface;
class CharacterInformation;
class ProcessableBuilding;

/**
 * A map entry point.
 *
 * Map entry points are linked to a location on the border of the map. They can generate different types of characters.
 * Currently, it only supports immigrant charaters.
 */
class MapEntryPoint : public AbstractProcessable
{
        const int MIN_IMMIGRANT_GENERATION_INTERVAL = 1;
        const int MAX_IMMIGRANT_GENERATION_INTERVAL = 90;

    private:
        CharacterFactoryInterface& characterFactory;
        MapCoordinates location;
        const CharacterInformation& immigrantConf;
        CycleDate nextImmigrantGenerationDate;
        QList<QPointer<ProcessableBuilding>> immigrantRequestQueue;

    public:
        MapEntryPoint(
            CharacterFactoryInterface& characterFactory,
            const MapCoordinates& location,
            const CharacterInformation& immigrantConf
        );

        /**
         * This will asynchronously generate an immigrant.
         */
        void requestImmigrant(ProcessableBuilding& issuer);

        virtual void process(const CycleDate& date) override;

    private:
        void setupNextImmigrantGenerationDate(const CycleDate& currentDate);
};

#endif // MAPENTRYPOINT_HPP
