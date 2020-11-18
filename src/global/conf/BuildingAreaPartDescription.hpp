#ifndef BUILDINGAREAPARTDESCRIPTION_HPP
#define BUILDINGAREAPARTDESCRIPTION_HPP

#include "src/engine/map/MapCoordinates.hpp"
#include "src/engine/map/MapSize.hpp"

class BuildingAreaPartDescription
{
        Q_DISABLE_COPY_MOVE(BuildingAreaPartDescription)

    public:
        enum Type {
            Classic,
            AttachedToRoad,  // Agora, Boulevard, Avenue, etc.
            AttachedToCoast, // Dock, Fishing wharf, etc.
            Road,            // CityEntryPoint, Road, etc.
            RoadLinker,      // Boulevard & Avenue
            Constructible,   // Agora, Sanctuary, etc.
        };

    private:
        MapCoordinates anchorCoordinates;
        MapSize areaSize;
        Type type;
        int altitude;

    public:
        /**
         * @brief Discribe a part of a static element area.
         *
         * @param anchorCoordinates The coordinates relative to the root coordinates of the building area.
         * @param areaSize          The size of the area part.
         * @param type              The type of area part.
         * @param altitude          The altitude of the area part.
         */
        BuildingAreaPartDescription(
            const MapCoordinates& anchorCoordinates,
            const MapSize& areaSize,
            Type type = Classic,
            int altitude = 0
        );
};

#endif // BUILDINGAREAPARTDESCRIPTION_HPP
