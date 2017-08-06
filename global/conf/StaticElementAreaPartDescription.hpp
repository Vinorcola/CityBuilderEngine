#ifndef STATICELEMENTAREAPARTDESCRIPTION_HPP
#define STATICELEMENTAREAPARTDESCRIPTION_HPP

#include <QtCore/QObject>

#include "engine/map/MapCoordinates.hpp"
#include "engine/map/MapSize.hpp"

class StaticElementAreaPartDescription : public QObject
{
        Q_OBJECT

    public:
        enum Type {
            Classic,
            AttachedToRoad,  // Agora, Boulevard, Avenue, etc.
            AttachedToCoast, // Dock, Fishing wharf, etc.
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
        StaticElementAreaPartDescription(QObject* parent, const MapCoordinates& anchorCoordinates, const MapSize& areaSize, Type type = Classic, int altitude = 0);
};

#endif // STATICELEMENTAREAPARTDESCRIPTION_HPP
