#ifndef MAPSCENE_HPP
#define MAPSCENE_HPP

#include <QGraphicsScene>

#include "engine/map/Map.hpp"
#include "viewer/DynamicElement.hpp"
#include "viewer/SelectionElement.hpp"
#include "viewer/Tile.hpp"





class MapScene : public QGraphicsScene
{
        Q_OBJECT


    private:
        const Map& map;
        QList<Tile*> tileList;
        QList<DynamicElement*> dynamicElementList;
        SelectionElement* selectionElement;



    public:
        MapScene(const Map& map);



        void requestBuilding(Map::StaticElementType type);



        void cancelBuildingRequest();



    public slots:
        void registerNewStaticElement(const QWeakPointer<AbstractStaticMapElement>& element);



        void registerNewDynamicElement(const QWeakPointer<AbstractDynamicMapElement>& element);



        /**
         * @brief Refresh the map.
         */
        void refresh();



    private:
        Tile* getTileAt(const MapCoordinates& location);

        void addStaticElementBuilding(Tile* tile, const MapSize& elementSize, const QPixmap& elementImage);

        /**
         * @brief Refresh the selection element.
         *
         * @note Please call only if element is visible.
         */
        void refreshSelectionElement();



    private slots:
        void currentTileChanged(Tile* currentTile);
};

#endif // MAPSCENE_HPP
