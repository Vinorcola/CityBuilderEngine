#ifndef MAPVIEWER_HPP
#define MAPVIEWER_HPP

#include <QGraphicsView>

#include "engine/map/Map.hpp"

class MapViewer : public QGraphicsView
{
        Q_OBJECT

    public:
        explicit MapViewer(Map& map, QWidget* parent = nullptr);

    public slots:
        void buildingRequest(const StaticElementInformation* elementConf);
};

#endif // MAPVIEWER_HPP
