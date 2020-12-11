#ifndef BUILDINGAREAINFORMATION_HPP
#define BUILDINGAREAINFORMATION_HPP

#include <QtCore/QHash>

#include "src/engine/map/MapCoordinates.hpp"
#include "src/engine/map/MapSize.hpp"
#include "src/global/Direction.hpp"
#include "src/defines.hpp"

class ImageSequenceInformation;
class ModelReader;
namespace YAML {
    class Node;
}

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

        struct Graphics {
            QString mainImagePath;
            QList<owner<const ImageSequenceInformation*>> activeAnimation;

            ~Graphics();
        };

        struct AreaPart {
            QPoint position;
            MapSize size;
            Type type;
            int altitude;
            Graphics graphics;

            AreaPart(
                const QPoint& position,
                const MapSize& size,
                const QString& graphicsBasePath,
                YAML::Node manifestNode,
                Type type = Type::Classic,
                int altitude = 0
            );
        };

    private:
        QHash<Direction, MapSize> sizes;
        QHash<Direction, QList<owner<const AreaPart*>>> area;

    public:
        BuildingAreaInformation(const ModelReader& model);
        ~BuildingAreaInformation();

        QList<Direction> getAvailableOrientations() const;
        QList<const AreaPart*> getAreaParts(Direction orientation) const;

        /**
         * @brief For backward compatibility. TO DELETE.
         *
         * Return the size of the first area part for west direction.
         */
        MapSize getSize(Direction orientation) const;

    private:
        static MapSize resolveSize(const QList<const AreaPart*>& areaParts);
};

#endif // BUILDINGAREAINFORMATION_HPP
