#ifndef CONSTRUCTIONCURSOR_HPP
#define CONSTRUCTIONCURSOR_HPP

#include <QtCore/QList>
#include <QtWidgets/QGraphicsObject>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QtWidgets/QGraphicsPolygonItem>

#include "src/engine/map/MapArea.hpp"
#include "src/defines.hpp"

class AreaCheckerInterface;
class BuildingImage;
class BuildingInformation;
class MapCoordinates;
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
                QGraphicsPixmapItem buildingGraphics;
                QGraphicsPolygonItem forbiddenAreaGraphics;

            public:
                Cursor(
                    QGraphicsItem* parent,
                    const Positioning& positioning,
                    const BuildingImage& buildingImage,
                    const MapSize& buildingSize
                );

                void updateStatus(bool isCoveredAreaFree);

                virtual QRectF boundingRect() const override;
                virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
        };

        class RoadPath {
            private:
                const Positioning& positioning;
                QGraphicsItem* parent;
                const QPixmap& image;
                const MapCoordinates origin;
                QList<MapArea> path;
                QList<owner<QGraphicsPixmapItem*>> graphics;

            public:
                RoadPath(
                    const Positioning& positioning,
                    QGraphicsItem* parent,
                    const MapCoordinates& origin,
                    const QPixmap& image
                );
                ~RoadPath();

                void refreshPath(const QList<MapCoordinates>& path);

                const MapCoordinates& getOrigin() const;
                const QList<MapArea>& getPath() const;

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
        MapArea coveredArea;
        bool isCoveredAreaFree;
        Cursor cursor;
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

        const MapArea& getCoveredArea() const;

        void displayAtLocation(const MapCoordinates& location);
        void refresh();

        virtual QRectF boundingRect() const override;
        virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    signals:
        void cancel();
        void construct(const BuildingInformation& buildingConf, QList<MapArea> area);

    protected:
        virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // CONSTRUCTIONCURSOR_HPP
