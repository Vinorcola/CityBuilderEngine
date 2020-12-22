#ifndef BUILDINGAREAINFORMATION_HPP
#define BUILDINGAREAINFORMATION_HPP

#include <QtCore/QHash>
#include <QtCore/QPoint>

#include "src/global/geometry/TileAreaSize.hpp"
#include "src/global/geometry/TileCoordinates.hpp"
#include "src/global/BuildingStatus.hpp"
#include "src/global/Direction.hpp"
#include "src/defines.hpp"

class ImageSequenceInformation;
class ModelReader;
namespace YAML {
    class Node;
}

using AnimationImages = QList<owner<const ImageSequenceInformation*>>;

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
            QHash<BuildingStatus, AnimationImages> animations;

            ~Graphics();
        };

        struct AreaPart {
            QPoint position;
            TileAreaSize size;
            Type type;
            int altitude;
            Graphics graphics;

            AreaPart(
                const QPoint& position,
                const TileAreaSize& size,
                const QString& graphicsBasePath,
                YAML::Node manifestNode,
                Type type = Type::Classic,
                int altitude = 0
            );
        };

    private:
        QHash<Direction, owner<TileAreaSize*>> sizes;////< Note: We have to use pointers because QHash require an emtpy constructor.
        QHash<Direction, QList<owner<const AreaPart*>>> area;

    public:
        BuildingAreaInformation(const QString& configDirectoryPath, const ModelReader& model);
        ~BuildingAreaInformation();

        QList<Direction> getAvailableOrientations() const;
        QList<const AreaPart*> getAreaParts(Direction orientation) const;

        TileAreaSize getSize(Direction orientation) const;

    private:
        static owner<TileAreaSize*> resolveSize(const QList<const AreaPart*>& areaParts);
};

#endif // BUILDINGAREAINFORMATION_HPP
