#ifndef SELECTIONELEMENT_HPP
#define SELECTIONELEMENT_HPP

#include <QtGui/QBrush>
#include <QtGui/QPen>
#include <QtWidgets/QGraphicsPolygonItem>

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
        const StaticElementInformation* currentElementConf;

    public:
        SelectionElement(const QSizeF& baseTileSize);

        /**
         * @brief Set the type of building selected.
         */
        void setBuildingType(const StaticElementInformation* currentElementConf);

        /**
         * @brief Set the selection element good.
         */
        void setGood();

        /**
         * @brief Set the selection element bad.
         */
        void setBad();

        /**
         * @brief Hide the selection element.
         */
        void hide();

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
