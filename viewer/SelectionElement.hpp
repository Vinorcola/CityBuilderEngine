#ifndef SELECTIONELEMENT_HPP
#define SELECTIONELEMENT_HPP

#include <QBrush>
#include <QGraphicsPolygonItem>
#include <QPen>

#include "engine/map/Map.hpp"
#include "engine/map/MapArea.hpp"
#include "viewer/Tile.hpp"





class SelectionElement : public QGraphicsPolygonItem
{
    private:
        QSizeF baseTileSize;
        QBrush goodBrush;
        QPen goodPen;
        QBrush badBrush;
        QPen badPen;
        QBrush* currentBrush;
        QPen* currentPen;
        MapArea currentArea;
        Map::StaticElementType currentBuildingType;



    public:
        SelectionElement(const QSizeF& baseTileSize);

        /**
         * @brief Set the type of building selected.
         * @param type
         */
        void setBuildingType(Map::StaticElementType type);

        /**
         * @brief Set the selection element good.
         */
        void setGood();

        /**
         * @brief Set the selection element bad.
         */
        void setBad();

        /**
         * @brief Attache the selection element to the given tile.
         * @param tile
         */
        void attachToTile(const Tile& tile);

        /**
         * @brief Get the area covered by the selection element.
         */
        const MapArea& getCoveredArea() const;



    private:
        /**
         * @brief Change the size of the selection element.
         *
         * @param size
         */
        void setSize(const MapSize& size);

        /**
         * @brief Refresh the painting.
         */
        void refresh();



    protected:
        virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
};

#endif // SELECTIONELEMENT_HPP
