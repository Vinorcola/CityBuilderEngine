#ifndef CONSTRUCTIONCURSOR_HPP
#define CONSTRUCTIONCURSOR_HPP

#include <QtCore/QList>
#include <QtWidgets/QGraphicsObject>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QtWidgets/QGraphicsPolygonItem>

#include "src/global/conf/BuildingAreaInformation.hpp"
#include "src/global/geometry/TileArea.hpp"
#include "src/global/geometry/TileCoordinates.hpp"
#include "src/global/Direction.hpp"
#include "src/defines.hpp"

class AreaCheckerInterface;
class BuildingImage;
class BuildingInformation;
class Positioning;
class RoadPathGeneratorInterface;

class ConstructionCursor : public QGraphicsObject
{
        Q_OBJECT

    private:
        enum class SelectionType {
            Road,
            Single,
        };

        class Cursor : public QGraphicsItem {
            private:
                QList<owner<QGraphicsPixmapItem*>> buildingGraphics;
                QGraphicsPolygonItem forbiddenAreaGraphics;
                QRectF bounds;

            public:
                Cursor(
                    QGraphicsItem* parent,
                    const Positioning& positioning,
                    Direction orientation,
                    const QList<const BuildingAreaInformation::AreaPart*>& areaInformation,
                    const BuildingImage& buildingImage,
                    const TileAreaSize& buildingSize
                );
                ~Cursor();

                void updateStatus(bool isCoveredAreaFree);

                virtual QRectF boundingRect() const override;
                virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
        };

        class RoadPath {
            private:
                const Positioning& positioning;
                QGraphicsItem* parent;
                const QPixmap& image;
                const TileCoordinates origin;
                QList<TileCoordinates> path;
                QList<owner<QGraphicsPixmapItem*>> graphics;

            public:
                RoadPath(
                    const Positioning& positioning,
                    QGraphicsItem* parent,
                    const TileCoordinates& origin,
                    const QPixmap& image
                );
                ~RoadPath();

                void refreshPath(const QList<TileCoordinates>& path);

                const TileCoordinates& getOrigin() const;
                const QList<TileCoordinates>& getPath() const;

            private:
                void resetPath();
        };

    private:
        const Positioning& positioning;
        const AreaCheckerInterface& areaChecker;
        const RoadPathGeneratorInterface& roadPathGenerator;
        const BuildingInformation& buildingConf;
        const BuildingImage& buildingImage;
        SelectionType selectionType;
        Direction orientation;
        TileArea coveredArea;
        bool isCoveredAreaFree;
        owner<Cursor*> cursor;
        optional<owner<RoadPath*>> roadPath;

    public:
        ConstructionCursor(
            const Positioning& positioning,
            const AreaCheckerInterface& areaChecker,
            const RoadPathGeneratorInterface& roadPathGenerator,
            const BuildingInformation& buildingConf,
            const BuildingImage& buildingImage
        );
        virtual ~ConstructionCursor();

        void displayAtLocation(const TileCoordinates& location);
        void rotateBuilding();
        void refresh();

        virtual QRectF boundingRect() const override;
        virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    signals:
        void cancel();
        void construct(const BuildingInformation& buildingConf, QList<TileCoordinates> locations, Direction direction);

    protected:
        virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    private:
        Direction resolveNextAvailableOrientation();
};

#endif // CONSTRUCTIONCURSOR_HPP
