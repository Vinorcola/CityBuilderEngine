#ifndef CONSTRUCTIONCURSOR_HPP
#define CONSTRUCTIONCURSOR_HPP

#include <QtWidgets/QGraphicsObject>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QtWidgets/QGraphicsPolygonItem>

#include "src/engine/map/MapArea.hpp"

class AreaChecker;
class BuildingImage;
class MapCoordinates;
class Positioning;

class ConstructionCursor : public QGraphicsObject
{
        Q_OBJECT

    private:
        const Positioning& positioning;
        const AreaChecker& areaChecker;
        MapArea coveredArea;
        bool isCoveredAreaFree;
        QGraphicsPixmapItem buildingImage;
        QGraphicsPolygonItem forbiddenAreaImage;

    public:
        ConstructionCursor(
            const Positioning& positioning,
            const AreaChecker& areaChecker,
            const BuildingImage& buildingImage,
            const MapSize& buildingSize
        );

        const MapArea& getCoveredArea() const;

        void displayAtLocation(const MapCoordinates& location);
        void refresh();

        virtual QRectF boundingRect() const override;
        virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    signals:
        void cancel();
        void construct(const MapArea& area);

    protected:
        virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // CONSTRUCTIONCURSOR_HPP
