#ifndef MAPENTRYPOINT_HPP
#define MAPENTRYPOINT_HPP

#include <functional>
#include <QtCore/QList>

#include "src/engine/map/MapCoordinates.hpp"
#include "src/engine/processing/CycleDate.hpp"
#include "src/engine/processing/AbstractProcessable.hpp"

class Character;
class CharacterFactoryInterface;
class CharacterInformation;

using OnCharacterCreationCallback = std::function<void(Character&)>;

/**
 * A map entry point.
 *
 * Map entry points are linked to a location on the border of the map. They can generate different types of characters.
 * Currently, it only supports immigrant charaters.
 */
class MapEntryPoint : public AbstractProcessable
{
    private:
        CharacterFactoryInterface& characterFactory;
        MapCoordinates location;
        const CharacterInformation& immigrantConf;
        CycleDate nextImmigrantGenerationDate;
        QList<OnCharacterCreationCallback> immigrantRequestQueue;

    public:
        MapEntryPoint(
            CharacterFactoryInterface& characterFactory,
            const MapCoordinates& location,
            const CharacterInformation& immigrantConf
        );

        /**
         * This will generate a new immigrant asynchronously, and will call the given callback.
         *
         * The generated immigrant will be unconfigured: it will have no target. It is the responsability on the
         * callback function to setup correctly the immigrant.
         */
        void requestImmigrant(OnCharacterCreationCallback onImmigrantCreation);

        virtual void process(const CycleDate& date) override;

    private:
        void setupNextImmigrantGenerationDate(const CycleDate& currentDate);
};

#endif // MAPENTRYPOINT_HPP
