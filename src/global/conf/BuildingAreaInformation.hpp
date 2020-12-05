#ifndef BUILDINGAREAINFORMATION_HPP
#define BUILDINGAREAINFORMATION_HPP

#include <QtCore/QHash>

#include "src/engine/map/MapCoordinates.hpp"
#include "src/engine/map/MapSize.hpp"
#include "src/global/Direction.hpp"
#include "src/defines.hpp"

class ModelReader;

class BuildingAreaInformation
{
        Q_DISABLE_COPY_MOVE(BuildingAreaInformation)

    public:
        enum Type {
            Classic,
            AttachedToRoad,  // Agora, Boulevard, Avenue, etc.
            AttachedToCoast, // Dock, Fishing wharf, etc.
            Road,            // Road
            RoadBlocker,     // Road blocker
            RoadLinker,      // Boulevard & Avenue
            Constructible,   // Agora, Sanctuary, etc.
        };

        struct AreaPart {
            MapCoordinates position;
            MapSize size;
            Type type;
            int altitude;

            AreaPart(const MapCoordinates& position, const MapSize& size, Type type = Type::Classic, int altitude = 0);
        };

    private:
        QHash<Direction, QList<owner<AreaPart*>>> area;

    public:
        BuildingAreaInformation(const ModelReader& model);
        ~BuildingAreaInformation();

        /**
         * @brief For backward compatibility. TO DELETE.
         *
         * Return the size of the first area part for west direction.
         */
        const MapSize& getSize() const;
};

#endif // BUILDINGAREAINFORMATION_HPP
