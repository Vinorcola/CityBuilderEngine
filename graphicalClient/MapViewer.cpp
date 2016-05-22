#include "MapViewer.hpp"

#include "graphicalClient/MapScene.hpp"





MapViewer::MapViewer(Map& map, QWidget* parent) :
    QGraphicsView(parent)
{
    setScene(new MapScene(map));
}
