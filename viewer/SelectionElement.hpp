#ifndef SELECTIONELEMENT_HPP
#define SELECTIONELEMENT_HPP

#include <QBrush>
#include <QGraphicsPolygonItem>
#include <QPen>

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



    public:
        SelectionElement(const QSizeF& baseTileSize);

        /**
         * @brief Change the size of the selection element.
         *
         * @param size
         */
        void setSize(const MapSize& size);

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
         * @brief Refresh the painting.
         */
        void refresh();
};

#endif // SELECTIONELEMENT_HPP
